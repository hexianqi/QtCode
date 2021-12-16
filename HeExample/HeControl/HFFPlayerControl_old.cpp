#include "HFFPlayerControl_old_p.h"
#include "HFFCmdUtil.h"

using namespace std;

#define CONFIG_AVFILTER 1

extern "C" {
#include "libavcodec/avfft.h"
#include "libavutil/bprint.h"
#include "libavutil/display.h"
#if CONFIG_AVFILTER
# include "libavfilter/avfilter.h"
# include "libavfilter/buffersink.h"
# include "libavfilter/buffersrc.h"
#endif
}

HE_BEGIN_NAMESPACE

/* no AV sync correction is done if below the minimum AV sync threshold */
#define AV_SYNC_THRESHOLD_MIN 0.04
/* AV sync correction is done if above the maximum AV sync threshold */
#define AV_SYNC_THRESHOLD_MAX 0.1
/* If a frame duration is longer than this, it will not be duplicated to compensate AV sync */
#define AV_SYNC_FRAMEDUP_THRESHOLD 0.1
/* no AV correction is done if too big error */
#define AV_SYNC_THRESHOLD_NO 10.0

#define VIDEO_QUEUE_SIZE 3
#define SUBPICTURE_QUEUE_SIZE 16
#define SAMPLE_QUEUE_SIZE 9
#define FRAME_QUEUE_SIZE FFMAX(SAMPLE_QUEUE_SIZE, FFMAX(VIDEO_QUEUE_SIZE, SUBPICTURE_QUEUE_SIZE))

#define MAX_QUEUE_SIZE (15 * 1024 * 1024)
#define MIN_FRAMES 25
#define EXTERNAL_CLOCK_MIN_FRAMES 2
#define EXTERNAL_CLOCK_MAX_FRAMES 10
/* external clock speed adjustment constants for realtime sources based on buffer fullness */
#define EXTERNAL_CLOCK_SPEED_MIN  0.900
#define EXTERNAL_CLOCK_SPEED_MAX  1.010
#define EXTERNAL_CLOCK_SPEED_STEP 0.001

/* we use about AUDIO_DIFF_AVG_NB A-V differences to make the average */
#define AUDIO_DIFF_AVG_NB   20

/* NOTE: the size must be big enough to compensate the hardware audio buffersize size */
/* TODO: We assume that a decoded and resampled frame fits into this buffer */
#define SAMPLE_ARRAY_SIZE (8 * 65536)
/* maximum audio speed change to get correct sync */
#define SAMPLE_CORRECTION_PERCENT_MAX 10

/* Minimum SDL audio buffer size, in samples. */
#define SDL_AUDIO_MIN_BUFFER_SIZE 512
/* Calculate actual buffer size keeping in mind not cause too frequent audio callbacks */
#define SDL_AUDIO_MAX_CALLBACKS_PER_SEC 30

/* Step size for volume control in dB */
#define SDL_VOLUME_STEP (0.75)

#define FF_QUIT_EVENT    (SDL_USEREVENT + 2)

#define CURSOR_HIDE_DELAY 1000000

/* polls for possible required screen refresh at least this often, should be less than 1/fps */
#define REFRESH_RATE 0.01

enum SyncMode
{
    SYNC_AUDIO_MASTER, /* default choice */
    SYNC_VIDEO_MASTER,
    SYNC_EXTERNAL_CLOCK, /* synchronize to an external clock */
};

enum ShowMode
{
    SHOW_MODE_NONE = -1,
    SHOW_MODE_VIDEO = 0,
    SHOW_MODE_WAVES,
    SHOW_MODE_RDFT,
    SHOW_MODE_NB
};

struct HVideoState;

struct HClock
{
public:
    void init(int *queue_serial);
    void set_clock(double pts, int serial);
    void set_clock_at(double pts, int serial, double time);
    void set_clock_speed(double speed);
    void sync_clock(HClock *slave);
    double get_clock();

public:
    double pts;           /* clock base */
    double pts_drift;     /* clock base minus time at which we updated the clock */
    double last_updated;
    double speed;
    int serial;           /* clock is based on a packet with this serial */
    int paused;
    int *queue_serial;    /* pointer to the current packet queue serial, used for obsolete clock detection */
};

struct HAudioParams
{
    int freq;
    int channels;
    int64_t channel_layout;
    AVSampleFormat fmt;
    int frame_size;
    int bytes_per_sec;
};

struct HPacketList
{
    AVPacket pkt;
    int serial;
    HPacketList *next;
};

struct HPacketQueue
{
public:
    bool init();
    int put(AVPacket *pkt);
    int put(int index);
    int get(AVPacket *pkt, int block, int *serial);
    void flush();
    void start();
    void abort();
    void destroy();

private:
    int put_private(AVPacket *pkt);

public:
    HPacketList *first_pkt;
    HPacketList *last_pkt;
    int nb_packets;
    int size;
    int64_t duration;
    int abort_request;
    int serial;
    SDL_mutex *mutex;
    SDL_cond *cond;
};

/* Common struct for handling all types of decoded data and allocated render buffers. */
struct HFrame
{
    AVFrame *frame;
    AVSubtitle sub;
    int serial;
    double pts;           /* presentation timestamp for the frame */
    double duration;      /* estimated duration of the frame */
    int64_t pos;          /* byte position of the frame in the input file */
    int width;
    int height;
    int format;
    AVRational sar;
    int uploaded;
    int flip_v;
};

struct HFrameQueue
{
public:
    bool init(HPacketQueue *pktq, int max_size, bool keep_last);
    int remaining();
    int64_t last_pos();
    void unref_item(HFrame *vp);
    HFrame *peek();
    HFrame *peek_next();
    HFrame *peek_last();
    HFrame *peek_writeable();
    HFrame *peek_readable();
    void push();
    void next();
    void signal();
    void destroy();

public:
    HFrame queue[FRAME_QUEUE_SIZE];
    int rindex;
    int windex;
    int size;
    int max_size;
    bool keep_last;
    int rindex_shown;
    HPacketQueue *pktq;
    SDL_mutex *mutex;
    SDL_cond *cond;
};

struct HDecoder
{
public:
    void init(HPacketQueue *queue, SDL_cond *empty_queue_cond);
    void set_codec_context(AVCodecContext *avctx);
    int decode(AVFrame *frame, AVSubtitle *sub);
    bool start(int (*fn)(void *), const char *thread_name, void *arg);
    void abort(HFrameQueue *fq);
    void destroy();

public:
    AVPacket pkt;
    HPacketQueue *queue;
    AVCodecContext *avctx;
    int pkt_serial;
    int finished;
    int packet_pending;
    SDL_cond *empty_queue_cond;
    int64_t start_pts;
    AVRational start_pts_tb;
    int64_t next_pts;
    AVRational next_pts_tb;
    SDL_Thread *decoder_tid;
};

struct HMediaStream
{
public:
    bool init(HVideoState *is, int max_size, bool keep_last, SDL_cond *empty_queue_cond);
    void destroy();
    bool open_stream(int index, AVFormatContext *ic, const char *forced_codec_name = nullptr);
    void close_stream(uint index);
    virtual bool open_else(AVCodecContext *avctx) = 0;
    virtual void close_else() = 0;

public:
    HPacketQueue packets;
    HFrameQueue frames;
    HDecoder decoder;

    int stream_index;
    int stream_last;
    int eof;

    AVFormatContext *ic;
    AVStream *stream;
    SwrContext *swr_ctx;
    HVideoState *is;
};

struct HVideoStream : public HMediaStream
{
public:
    bool open_else(AVCodecContext *avctx) override;
    void close_else() override;

public:
    int queue_attachments_req;
};

struct HAudioStream : public HMediaStream
{
public:
    bool open_else(AVCodecContext *avctx) override;
    void close_else() override;
#if CONFIG_AVFILTER
    int configure_filters(const char *afilters, int force_output_format);
#endif

public:
    uint8_t *buf;
    uint8_t *buf1;
    unsigned int buf_size; /* in bytes */
    unsigned int buf1_size;
    int buf_index; /* in bytes */
    double diff_cum; /* used for AV difference average computation */
    double diff_avg_coef;
    double diff_threshold;
    int diff_avg_count;
    int hw_buf_size;

    RDFTContext *rdft;
    FFTSample *rdft_data;
    int rdft_bits;
    HAudioParams src;
    HAudioParams tgt;

#if CONFIG_AVFILTER
    HAudioParams filter_src;
    AVFilterContext *in_filter;   // the first filter in the audio chain
    AVFilterContext *out_filter;  // the last filter in the audio chain
    AVFilterGraph *graph;         // audio filter graph
#endif
};

struct HSubtitleStream : public HMediaStream
{
public:
    bool open_else(AVCodecContext *avctx) override;
    void close_else() override;
};

struct HVideoState
{
public:
    bool init(const char *filename, AVInputFormat *iformat);
//    int open_stream(int index);
    void destroy();
    //    void close_stream(int index);

public:
    int stream_has_enough_packets(AVStream *st, int stream_id, HPacketQueue *queue);
    int get_master_sync_type();
    double get_master_clock();
    void check_external_clock_speed();
    double vp_duration(HFrame *vp, HFrame *nextvp);
    double compute_target_delay(double delay);

    int audio_decode_frame();
    int synchronize_audio(int nb_samples);
    void update_sample_display(short *samples, int samples_size);

    int get_video_frame(AVFrame *frame);
    int queue_picture(AVFrame *src_frame, double pts, double duration, int64_t pos, int serial);
    void update_video_pts(double pts, int64_t pos, int serial);
    int video_open();
    void video_refresh(double *remaining_time);
    void video_display();
    void video_audio_display();
    void video_image_display();

public:
#if CONFIG_AVFILTER
//    int configure_filtergraph(AVFilterGraph *graph, const char *filtergraph, AVFilterContext *source_ctx, AVFilterContext *sink_ctx);
//    int configure_audio_filters(const char *afilters, int force_output_format);
    int configure_video_filters(AVFilterGraph *graph, const char *vfilters, AVFrame *frame);
#endif


public:
    void seek(int64_t pos, int64_t rel, int seek_by_bytes);
    void seek_chapter(int incr);
    void step_to_next_frame();
    void toggle_pause();
    void toggle_mute();
    void toggle_full_screen();
    void toggle_audio_display();
    void update_volume(int sign, double step);
    void cycle_channel(int codec_type);

public:
    SDL_Thread *read_tid;
    AVInputFormat *iformat;
    int abort_request;
    int force_refresh;
    int paused;
    int last_paused;
    int queue_attachments_req;
    int seek_req;
    int seek_flags;
    int64_t seek_pos;
    int64_t seek_rel;
    int read_pause_return;
    AVFormatContext *ic;
    int realtime;

    HClock audclk;
    HClock vidclk;
    HClock extclk;

    //    HFrameQueue pictq;
    //    HFrameQueue subpq;
    //    HFrameQueue sampq;

    //    HDecoder auddec;
    //    HDecoder viddec;
    //    HDecoder subdec;

    //    int audio_stream;

    SyncMode sync_mode;
    ShowMode show_mode;

    double audio_clock;
    int audio_clock_serial;
//    double audio_diff_cum; /* used for AV difference average computation */
//    double audio_diff_avg_coef;
//    double audio_diff_threshold;
//    int audio_diff_avg_count;
    //    AVStream *audio_st;
    //    HPacketQueue audioq;
    //    int audio_hw_buf_size;
    //    uint8_t *audio_buf;
    //    uint8_t *audio_buf1;
    //    unsigned int audio_buf_size; /* in bytes */
    //    unsigned int audio_buf1_size;
    //    int audio_buf_index; /* in bytes */
    int audio_write_buf_size;
    int audio_volume;
    int muted;
//    HAudioParams audio_src;
//#if CONFIG_AVFILTER
//    HAudioParams audio_filter_src;
//#endif
//    HAudioParams audio_tgt;
    //    SwrContext *swr_ctx;
    int frame_drops_early;
    int frame_drops_late;


    int16_t sample_array[SAMPLE_ARRAY_SIZE];
    int sample_array_index;
    int last_i_start;
    //    RDFTContext *rdft;
    //    int rdft_bits;
    //    FFTSample *rdft_data;
    int xpos;
    double last_vis_time;
    SDL_Texture *vis_texture;
    SDL_Texture *sub_texture;
    SDL_Texture *vid_texture;

    //    int subtitle_stream;
    //    AVStream *subtitle_st;
    //    HPacketQueue subtitleq;

    double frame_timer;
    double frame_last_returned_time;
    double frame_last_filter_delay;
    //    int video_stream;
    //    AVStream *video_st;
    //    HPacketQueue videoq;
    double max_frame_duration;      // maximum duration of a frame - above this, we consider the jump a timestamp discontinuity
    struct SwsContext *img_convert_ctx;
    struct SwsContext *sub_convert_ctx;
    int eof;

    char *filename;
    int width, height, xleft, ytop;
    int step;

#if CONFIG_AVFILTER
    int vfilter_idx;
    AVFilterContext *in_video_filter;   // the first filter in the video chain
    AVFilterContext *out_video_filter;  // the last filter in the video chain
//    AVFilterContext *in_audio_filter;   // the first filter in the audio chain
//    AVFilterContext *out_audio_filter;  // the last filter in the audio chain
//    AVFilterGraph *agraph;              // audio filter graph
#endif

    //    int last_video_stream, last_audio_stream, last_subtitle_stream;

    SDL_cond *continue_read_thread;

public:
    HVideoStream video;
    HAudioStream audio;
    HSubtitleStream subtitle;
};

    /* options specified by the user */
    static AVInputFormat *file_iformat;
static const char *input_filename;
static const char *window_title;
static int default_width  = 640;
static int default_height = 480;
static int screen_width  = 0;
static int screen_height = 0;
static int screen_left = SDL_WINDOWPOS_CENTERED;
static int screen_top = SDL_WINDOWPOS_CENTERED;
static int audio_disable;
static int video_disable;
static int subtitle_disable;
static int display_disable;
static int borderless;
static int alwaysontop;
static const char* wanted_stream_spec[AVMEDIA_TYPE_NB] = {0};
static int seek_by_bytes = -1;
static float seek_interval = 10;
static int startup_volume = 100;
static int show_status = -1;
static SyncMode av_sync_type = SYNC_AUDIO_MASTER;
static int64_t start_time = AV_NOPTS_VALUE;
static int64_t duration = AV_NOPTS_VALUE;
static int fast = 0;
static int genpts = 0;
static int lowres = 0;
static int decoder_reorder_pts = -1;
static int autoexit;
static int exit_on_keydown;
static int exit_on_mousedown;
static int loop = 1;
static int framedrop = -1;
static int infinite_buffer = -1;
static ShowMode show_mode = SHOW_MODE_NONE;
static const char *audio_codec_name;
static const char *subtitle_codec_name;
static const char *video_codec_name;
double rdftspeed = 0.02;
static int64_t cursor_last_shown;
static int cursor_hidden = 0;
#if CONFIG_AVFILTER
static const char **vfilters_list = NULL;
static int nb_vfilters = 0;
static char *afilters = NULL;
#endif
static int autorotate = 1;
static int find_stream_info = 1;
static int filter_nbthreads = 0;

    /* current context */
    static int is_full_screen;
static int64_t audio_callback_time;

//    static AVPacket flush_pkt;
static unsigned sws_flags = SWS_BICUBIC;

    static SDL_Window *window;
static SDL_Renderer *renderer;
static SDL_RendererInfo renderer_info;
static SDL_AudioDeviceID audio_dev;

    static const struct TextureFormatEntry {
    enum AVPixelFormat format;
    int texture_fmt;
    } sdl_texture_format_map[] = {
    { AV_PIX_FMT_RGB8,           SDL_PIXELFORMAT_RGB332 },
    { AV_PIX_FMT_RGB444,         SDL_PIXELFORMAT_RGB444 },
    { AV_PIX_FMT_RGB555,         SDL_PIXELFORMAT_RGB555 },
    { AV_PIX_FMT_BGR555,         SDL_PIXELFORMAT_BGR555 },
    { AV_PIX_FMT_RGB565,         SDL_PIXELFORMAT_RGB565 },
    { AV_PIX_FMT_BGR565,         SDL_PIXELFORMAT_BGR565 },
    { AV_PIX_FMT_RGB24,          SDL_PIXELFORMAT_RGB24 },
    { AV_PIX_FMT_BGR24,          SDL_PIXELFORMAT_BGR24 },
    { AV_PIX_FMT_0RGB32,         SDL_PIXELFORMAT_RGB888 },
    { AV_PIX_FMT_0BGR32,         SDL_PIXELFORMAT_BGR888 },
    { AV_PIX_FMT_NE(RGB0, 0BGR), SDL_PIXELFORMAT_RGBX8888 },
    { AV_PIX_FMT_NE(BGR0, 0RGB), SDL_PIXELFORMAT_BGRX8888 },
    { AV_PIX_FMT_RGB32,          SDL_PIXELFORMAT_ARGB8888 },
    { AV_PIX_FMT_RGB32_1,        SDL_PIXELFORMAT_RGBA8888 },
    { AV_PIX_FMT_BGR32,          SDL_PIXELFORMAT_ABGR8888 },
    { AV_PIX_FMT_BGR32_1,        SDL_PIXELFORMAT_BGRA8888 },
    { AV_PIX_FMT_YUV420P,        SDL_PIXELFORMAT_IYUV },
    { AV_PIX_FMT_YUYV422,        SDL_PIXELFORMAT_YUY2 },
    { AV_PIX_FMT_UYVY422,        SDL_PIXELFORMAT_UYVY },
    { AV_PIX_FMT_NONE,           SDL_PIXELFORMAT_UNKNOWN },
    };

AVDictionary *sws_dict;
//AVDictionary *swr_opts;
//AVDictionary *format_opts;
//AVDictionary *codec_opts;
//AVDictionary *resample_opts;

int compute_mod(int a, int b)
{
    return a < 0 ? a%b + b : a%b;
}

//void uninit_opts(void)
//{
//    av_dict_free(&swr_opts);
//    av_dict_free(&sws_dict);
//    av_dict_free(&format_opts);
//    av_dict_free(&codec_opts);
//    av_dict_free(&resample_opts);
//}

//int check_stream_specifier(AVFormatContext *s, AVStream *st, const char *spec)
//{
//    int ret = avformat_match_stream_specifier(s, st, spec);
//    if (ret < 0)
//        av_log(s, AV_LOG_ERROR, "Invalid stream specifier: %s.\n", spec);
//    return ret;
//}

//AVDictionary *filter_codec_opts(AVDictionary *opts, AVCodecID codec_id, AVFormatContext *s, AVStream *st, AVCodec *codec)
//{
//    AVDictionary *ret = nullptr;
//    AVDictionaryEntry *t = nullptr;
//    char prefix = 0;
//    auto cc = avcodec_get_class();
//    auto flags = s->oformat ? AV_OPT_FLAG_ENCODING_PARAM : AV_OPT_FLAG_DECODING_PARAM;

//    if (!codec)
//        codec = s->oformat ? avcodec_find_encoder(codec_id) : avcodec_find_decoder(codec_id);

//    switch (st->codecpar->codec_type)
//    {
//    case AVMEDIA_TYPE_VIDEO:
//        prefix  = 'v';
//        flags  |= AV_OPT_FLAG_VIDEO_PARAM;
//        break;
//    case AVMEDIA_TYPE_AUDIO:
//        prefix  = 'a';
//        flags  |= AV_OPT_FLAG_AUDIO_PARAM;
//        break;
//    case AVMEDIA_TYPE_SUBTITLE:
//        prefix  = 's';
//        flags  |= AV_OPT_FLAG_SUBTITLE_PARAM;
//        break;
//    default:
//        break;
//    }

//    while ((t = av_dict_get(opts, "", t, AV_DICT_IGNORE_SUFFIX)))
//    {
//        /* check stream specification in opt name */
//        char *p = strchr(t->key, ':');
//        if (p)
//        {
//            auto temp = check_stream_specifier(s, st, p + 1);
//            if (temp == 1)
//                *p = 0;
//            else if (temp == 0)
//                continue;
//            else
//                return nullptr;
//        }
//        if (av_opt_find(&cc, t->key, nullptr, flags, AV_OPT_SEARCH_FAKE_OBJ) ||
//            !codec ||
//            (codec->priv_class && av_opt_find(&codec->priv_class, t->key, nullptr, flags, AV_OPT_SEARCH_FAKE_OBJ)))
//            av_dict_set(&ret, t->key, t->value, 0);
//        else if (t->key[0] == prefix && av_opt_find(&cc, t->key + 1, nullptr, flags, AV_OPT_SEARCH_FAKE_OBJ))
//            av_dict_set(&ret, t->key + 1, t->value, 0);

//        if (p)
//            *p = ':';
//    }
//    return ret;
//}

//AVDictionary **setup_find_stream_info_opts(AVFormatContext *s, AVDictionary *codec_opts)
//{
//    if (!s->nb_streams)
//        return nullptr;

//    AVDictionary **opts;
//    opts = (AVDictionary **)av_mallocz_array(s->nb_streams, sizeof(*opts));
//    if (!opts)
//    {
//        av_log(nullptr, AV_LOG_ERROR, "Could not alloc memory for stream options.\n");
//        return nullptr;
//    }
//    for (uint i = 0; i < s->nb_streams; i++)
//        opts[i] = filter_codec_opts(codec_opts, s->streams[i]->codecpar->codec_id, s, s->streams[i], nullptr);
//    return opts;
//}

#if CONFIG_AVFILTER
int configure_filtergraph(AVFilterGraph *graph, const char *filtergraph, AVFilterContext *source_ctx, AVFilterContext *sink_ctx)
{
    int ret, i;
    int nb_filters = graph->nb_filters;
    AVFilterInOut *outputs = NULL, *inputs = NULL;

    if (filtergraph)
    {
        outputs = avfilter_inout_alloc();
        inputs  = avfilter_inout_alloc();
        if (!outputs || !inputs)
        {
            ret = AVERROR(ENOMEM);
            goto fail;
        }

        outputs->name       = av_strdup("in");
        outputs->filter_ctx = source_ctx;
        outputs->pad_idx    = 0;
        outputs->next       = nullptr;
        inputs->name        = av_strdup("out");
        inputs->filter_ctx  = sink_ctx;
        inputs->pad_idx     = 0;
        inputs->next        = nullptr;

        if ((ret = avfilter_graph_parse_ptr(graph, filtergraph, &inputs, &outputs, NULL)) < 0)
            goto fail;
    }
    else
    {
        if ((ret = avfilter_link(source_ctx, 0, sink_ctx, 0)) < 0)
            goto fail;
    }

    /* Reorder the filters to ensure that inputs of the custom filters are merged first */
    for (i = 0; i < graph->nb_filters - nb_filters; i++)
        FFSWAP(AVFilterContext*, graph->filters[i], graph->filters[i + nb_filters]);

    ret = avfilter_graph_config(graph, nullptr);
fail:
    avfilter_inout_free(&outputs);
    avfilter_inout_free(&inputs);
    return ret;
}
#endif

void calc_display_rect(SDL_Rect *rect,
                       int scr_xleft, int scr_ytop, int scr_width, int scr_height,
                       int pic_width, int pic_height, AVRational pic_sar)
{
    AVRational aspect_ratio = pic_sar;
    int64_t width, height, x, y;

    if (av_cmp_q(aspect_ratio, av_make_q(0, 1)) <= 0)
        aspect_ratio = av_make_q(1, 1);

    aspect_ratio = av_mul_q(aspect_ratio, av_make_q(pic_width, pic_height));

    /* XXX: we suppose the screen has a 1.0 pixel ratio */
    height = scr_height;
    width = av_rescale(height, aspect_ratio.num, aspect_ratio.den) & ~1;
    if (width > scr_width)
    {
        width = scr_width;
        height = av_rescale(width, aspect_ratio.den, aspect_ratio.num) & ~1;
    }
    x = (scr_width - width) / 2;
    y = (scr_height - height) / 2;
    rect->x = scr_xleft + x;
    rect->y = scr_ytop  + y;
    rect->w = FFMAX((int)width,  1);
    rect->h = FFMAX((int)height, 1);
}

//double get_rotation(AVStream *st)
//{
//    uint8_t* displaymatrix = av_stream_get_side_data(st, AV_PKT_DATA_DISPLAYMATRIX, nullptr);
//    double theta = 0;
//    if (displaymatrix)
//        theta = -av_display_rotation_get((int32_t*) displaymatrix);

//    theta -= 360 * floor(theta/360 + 0.9/360);

//    if (fabs(theta - 90*round(theta/90)) > 2)
//        av_log(nullptr, AV_LOG_WARNING, "Odd rotation angle.\n"
//                                        "If you want to help, upload a sample "
//                                        "of this file to https://streams.videolan.org/upload/ "
//                                        "and contact the ffmpeg-devel mailing list. (ffmpeg-devel@ffmpeg.org)");
//    return theta;
//}

//int64_t get_valid_channel_layout(int64_t channel_layout, int channels)
//{
//    return channel_layout && av_get_channel_layout_nb_channels(channel_layout) == channels ? channel_layout : 0;
//}

void set_default_window_size(int width, int height, AVRational sar)
{
    SDL_Rect rect;
    int max_width  = screen_width  ? screen_width  : INT_MAX;
    int max_height = screen_height ? screen_height : INT_MAX;
    if (max_width == INT_MAX && max_height == INT_MAX)
        max_height = height;
    calc_display_rect(&rect, 0, 0, max_width, max_height, width, height, sar);
    default_width  = rect.w;
    default_height = rect.h;
}

void fill_rectangle(int x, int y, int w, int h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    if (w && h)
        SDL_RenderFillRect(renderer, &rect);
}

void get_sdl_pix_fmt_and_blendmode(int format, Uint32 *sdl_pix_fmt, SDL_BlendMode *sdl_blendmode)
{
    *sdl_blendmode = SDL_BLENDMODE_NONE;
    *sdl_pix_fmt = SDL_PIXELFORMAT_UNKNOWN;
    if (format == AV_PIX_FMT_RGB32   ||
        format == AV_PIX_FMT_RGB32_1 ||
        format == AV_PIX_FMT_BGR32   ||
        format == AV_PIX_FMT_BGR32_1)
        *sdl_blendmode = SDL_BLENDMODE_BLEND;
    for (uint i = 0; i < FF_ARRAY_ELEMS(sdl_texture_format_map) - 1; i++)
    {
        if (format == sdl_texture_format_map[i].format)
        {
            *sdl_pix_fmt = sdl_texture_format_map[i].texture_fmt;
            return;
        }
    }
}

void set_sdl_yuv_conversion_mode(AVFrame *frame)
{
    SDL_YUV_CONVERSION_MODE mode = SDL_YUV_CONVERSION_AUTOMATIC;
    if (frame && (frame->format == AV_PIX_FMT_YUV420P || frame->format == AV_PIX_FMT_YUYV422 || frame->format == AV_PIX_FMT_UYVY422))
    {
        if (frame->color_range == AVCOL_RANGE_JPEG)
            mode = SDL_YUV_CONVERSION_JPEG;
        else if (frame->colorspace == AVCOL_SPC_BT709)
            mode = SDL_YUV_CONVERSION_BT709;
        else if (frame->colorspace == AVCOL_SPC_BT470BG || frame->colorspace == AVCOL_SPC_SMPTE170M || frame->colorspace == AVCOL_SPC_SMPTE240M)
            mode = SDL_YUV_CONVERSION_BT601;
    }
    SDL_SetYUVConversionMode(mode);
}

int realloc_texture(SDL_Texture **texture, Uint32 new_format, int new_width, int new_height, SDL_BlendMode blendmode, int init_texture)
{
    Uint32 format;
    int access, w, h;
    if (!*texture || SDL_QueryTexture(*texture, &format, &access, &w, &h) < 0 || new_width != w || new_height != h || new_format != format) {
        void *pixels;
        int pitch;
        if (*texture)
            SDL_DestroyTexture(*texture);
        if (!(*texture = SDL_CreateTexture(renderer, new_format, SDL_TEXTUREACCESS_STREAMING, new_width, new_height)))
            return -1;
        if (SDL_SetTextureBlendMode(*texture, blendmode) < 0)
            return -1;
        if (init_texture) {
            if (SDL_LockTexture(*texture, NULL, &pixels, &pitch) < 0)
                return -1;
            memset(pixels, 0, pitch * new_height);
            SDL_UnlockTexture(*texture);
        }
        av_log(NULL, AV_LOG_VERBOSE, "Created %dx%d texture with %s.\n", new_width, new_height, SDL_GetPixelFormatName(new_format));
    }
    return 0;
}

int upload_texture(SDL_Texture **tex, AVFrame *frame, struct SwsContext **img_convert_ctx) {
    int ret = 0;
    Uint32 sdl_pix_fmt;
    SDL_BlendMode sdl_blendmode;
    get_sdl_pix_fmt_and_blendmode(frame->format, &sdl_pix_fmt, &sdl_blendmode);
    if (realloc_texture(tex, sdl_pix_fmt == SDL_PIXELFORMAT_UNKNOWN ? SDL_PIXELFORMAT_ARGB8888 : sdl_pix_fmt, frame->width, frame->height, sdl_blendmode, 0) < 0)
        return -1;
    switch (sdl_pix_fmt) {
    case SDL_PIXELFORMAT_UNKNOWN:
        /* This should only happen if we are not using avfilter... */
        *img_convert_ctx = sws_getCachedContext(*img_convert_ctx,
                                                frame->width, frame->height, (AVPixelFormat)frame->format, frame->width, frame->height,
                                                AV_PIX_FMT_BGRA, sws_flags, NULL, NULL, NULL);
        if (*img_convert_ctx != NULL) {
            uint8_t *pixels[4];
            int pitch[4];
            if (!SDL_LockTexture(*tex, NULL, (void **)pixels, pitch)) {
                sws_scale(*img_convert_ctx, (const uint8_t * const *)frame->data, frame->linesize,
                          0, frame->height, pixels, pitch);
                SDL_UnlockTexture(*tex);
            }
        } else {
            av_log(NULL, AV_LOG_FATAL, "Cannot initialize the conversion context\n");
            ret = -1;
        }
        break;
    case SDL_PIXELFORMAT_IYUV:
        if (frame->linesize[0] > 0 && frame->linesize[1] > 0 && frame->linesize[2] > 0) {
            ret = SDL_UpdateYUVTexture(*tex, NULL, frame->data[0], frame->linesize[0],
                                       frame->data[1], frame->linesize[1],
                                       frame->data[2], frame->linesize[2]);
        } else if (frame->linesize[0] < 0 && frame->linesize[1] < 0 && frame->linesize[2] < 0) {
            ret = SDL_UpdateYUVTexture(*tex, NULL, frame->data[0] + frame->linesize[0] * (frame->height                    - 1), -frame->linesize[0],
                                       frame->data[1] + frame->linesize[1] * (AV_CEIL_RSHIFT(frame->height, 1) - 1), -frame->linesize[1],
                                       frame->data[2] + frame->linesize[2] * (AV_CEIL_RSHIFT(frame->height, 1) - 1), -frame->linesize[2]);
        } else {
            av_log(NULL, AV_LOG_ERROR, "Mixed negative and positive linesizes are not supported.\n");
            return -1;
        }
        break;
    default:
        if (frame->linesize[0] < 0) {
            ret = SDL_UpdateTexture(*tex, NULL, frame->data[0] + frame->linesize[0] * (frame->height - 1), -frame->linesize[0]);
        } else {
            ret = SDL_UpdateTexture(*tex, NULL, frame->data[0], frame->linesize[0]);
        }
        break;
    }
    return ret;
}

/* prepare a new audio buffer */
void sdl_audio_callback(void *opaque, Uint8 *stream, int len)
{
    HVideoState *is = static_cast<HVideoState *>(opaque);
    int audio_size, len1;

    audio_callback_time = av_gettime_relative();

    while (len > 0) {
        if (is->audio.buf_index >= is->audio.buf_size) {
            audio_size = is->audio_decode_frame();
            if (audio_size < 0) {
                /* if error, just output silence */
                is->audio.buf = NULL;
                is->audio.buf_size = SDL_AUDIO_MIN_BUFFER_SIZE / is->audio.tgt.frame_size * is->audio.tgt.frame_size;
            } else {
                if (is->show_mode != SHOW_MODE_VIDEO)
                    is->update_sample_display((int16_t *)is->audio.buf, audio_size);
                is->audio.buf_size = audio_size;
            }
            is->audio.buf_index = 0;
        }
        len1 = is->audio.buf_size - is->audio.buf_index;
        if (len1 > len)
            len1 = len;
        if (!is->muted && is->audio.buf && is->audio_volume == SDL_MIX_MAXVOLUME)
            memcpy(stream, (uint8_t *)is->audio.buf + is->audio.buf_index, len1);
        else {
            memset(stream, 0, len1);
            if (!is->muted && is->audio.buf)
                SDL_MixAudioFormat(stream, (uint8_t *)is->audio.buf + is->audio.buf_index, AUDIO_S16SYS, len1, is->audio_volume);
        }
        len -= len1;
        stream += len1;
        is->audio.buf_index += len1;
    }
    is->audio_write_buf_size = is->audio.buf_size - is->audio.buf_index;
    /* Let's assume the audio driver that is used by SDL has two periods. */
    if (!isnan(is->audio_clock))
    {
        is->audclk.set_clock_at(is->audio_clock - (double)(2 * is->audio.hw_buf_size + is->audio_write_buf_size) / is->audio.tgt.bytes_per_sec, is->audio_clock_serial, audio_callback_time / 1000000.0);
        is->extclk.sync_clock(&is->audclk);
    }
}

int audio_open(void *opaque, int64_t wanted_channel_layout, int wanted_nb_channels, int wanted_sample_rate, HAudioParams *audio_hw_params)
{
    SDL_AudioSpec wanted_spec, spec;
    const char *env;
    static const int next_nb_channels[] = {0, 0, 1, 6, 2, 6, 4, 6};
    static const int next_sample_rates[] = {0, 44100, 48000, 96000, 192000};
    int next_sample_rate_idx = FF_ARRAY_ELEMS(next_sample_rates) - 1;

    env = SDL_getenv("SDL_AUDIO_CHANNELS");
    if (env) {
        wanted_nb_channels = atoi(env);
        wanted_channel_layout = av_get_default_channel_layout(wanted_nb_channels);
    }
    if (!wanted_channel_layout || wanted_nb_channels != av_get_channel_layout_nb_channels(wanted_channel_layout)) {
        wanted_channel_layout = av_get_default_channel_layout(wanted_nb_channels);
        wanted_channel_layout &= ~AV_CH_LAYOUT_STEREO_DOWNMIX;
    }
    wanted_nb_channels = av_get_channel_layout_nb_channels(wanted_channel_layout);
    wanted_spec.channels = wanted_nb_channels;
    wanted_spec.freq = wanted_sample_rate;
    if (wanted_spec.freq <= 0 || wanted_spec.channels <= 0) {
        av_log(NULL, AV_LOG_ERROR, "Invalid sample rate or channel count!\n");
        return -1;
    }
    while (next_sample_rate_idx && next_sample_rates[next_sample_rate_idx] >= wanted_spec.freq)
        next_sample_rate_idx--;
    wanted_spec.format = AUDIO_S16SYS;
    wanted_spec.silence = 0;
    wanted_spec.samples = FFMAX(SDL_AUDIO_MIN_BUFFER_SIZE, 2 << av_log2(wanted_spec.freq / SDL_AUDIO_MAX_CALLBACKS_PER_SEC));
    wanted_spec.callback = sdl_audio_callback;
    wanted_spec.userdata = opaque;
    while (!(audio_dev = SDL_OpenAudioDevice(NULL, 0, &wanted_spec, &spec, SDL_AUDIO_ALLOW_FREQUENCY_CHANGE | SDL_AUDIO_ALLOW_CHANNELS_CHANGE))) {
        av_log(NULL, AV_LOG_WARNING, "SDL_OpenAudio (%d channels, %d Hz): %s\n",
               wanted_spec.channels, wanted_spec.freq, SDL_GetError());
        wanted_spec.channels = next_nb_channels[FFMIN(7, wanted_spec.channels)];
        if (!wanted_spec.channels) {
            wanted_spec.freq = next_sample_rates[next_sample_rate_idx--];
            wanted_spec.channels = wanted_nb_channels;
            if (!wanted_spec.freq) {
                av_log(NULL, AV_LOG_ERROR,
                       "No more combinations to try, audio open failed\n");
                return -1;
            }
        }
        wanted_channel_layout = av_get_default_channel_layout(wanted_spec.channels);
    }
    if (spec.format != AUDIO_S16SYS) {
        av_log(NULL, AV_LOG_ERROR,
               "SDL advised audio format %d is not supported!\n", spec.format);
        return -1;
    }
    if (spec.channels != wanted_spec.channels) {
        wanted_channel_layout = av_get_default_channel_layout(spec.channels);
        if (!wanted_channel_layout) {
            av_log(NULL, AV_LOG_ERROR,
                   "SDL advised channel count %d is not supported!\n", spec.channels);
            return -1;
        }
    }

    audio_hw_params->fmt = AV_SAMPLE_FMT_S16;
    audio_hw_params->freq = spec.freq;
    audio_hw_params->channel_layout = wanted_channel_layout;
    audio_hw_params->channels =  spec.channels;
    audio_hw_params->frame_size = av_samples_get_buffer_size(NULL, audio_hw_params->channels, 1, audio_hw_params->fmt, 1);
    audio_hw_params->bytes_per_sec = av_samples_get_buffer_size(NULL, audio_hw_params->channels, audio_hw_params->freq, audio_hw_params->fmt, 1);
    if (audio_hw_params->bytes_per_sec <= 0 || audio_hw_params->frame_size <= 0) {
        av_log(NULL, AV_LOG_ERROR, "av_samples_get_buffer_size failed\n");
        return -1;
    }
    return spec.size;
}

int decode_interrupt(void *ctx)
{
    return static_cast<HVideoState *>(ctx)->abort_request;
}

//int is_realtime(AVFormatContext *s)
//{
//    if (!strcmp(s->iformat->name, "rtp") || !strcmp(s->iformat->name, "rtsp") || !strcmp(s->iformat->name, "sdp"))
//        return 1;
//    if (s->pb && (!strncmp(s->url, "rtp:", 4) || !strncmp(s->url, "udp:", 4)))
//        return 1;
//    return 0;
//}

//int cmp_audio_fmts(AVSampleFormat fmt1, int64_t channel_count1, AVSampleFormat fmt2, int64_t channel_count2)
//{
//    /* If channel count == 1, planar and non-planar formats are the same */
//    if (channel_count1 == 1 && channel_count2 == 1)
//        return av_get_packed_sample_fmt(fmt1) != av_get_packed_sample_fmt(fmt2);
//    return channel_count1 != channel_count2 || fmt1 != fmt2;
//}

int audio_thread(void *arg)
{
    HVideoState *is = static_cast<HVideoState *>(arg);
    AVFrame *frame = av_frame_alloc();
    HFrame *af;
#if CONFIG_AVFILTER
    int last_serial = -1;
    int64_t dec_channel_layout;
    int reconfigure;
#endif
    int got_frame = 0;
    AVRational tb;
    int ret = 0;

    if (!frame)
        return AVERROR(ENOMEM);

    do {
        if ((got_frame = is->audio.decoder.decode(frame, NULL)) < 0)
            goto the_end;

        if (got_frame) {
            tb = (AVRational){1, frame->sample_rate};

#if CONFIG_AVFILTER
            dec_channel_layout = get_valid_channel_layout(frame->channel_layout, frame->channels);

            reconfigure =
                cmp_audio_fmts(is->audio.filter_src.fmt, is->audio.filter_src.channels,
                               (AVSampleFormat)frame->format, frame->channels)    ||
                is->audio.filter_src.channel_layout != dec_channel_layout ||
                is->audio.filter_src.freq           != frame->sample_rate ||
                is->audio.decoder.pkt_serial               != last_serial;

            if (reconfigure) {
                char buf1[1024], buf2[1024];
                av_get_channel_layout_string(buf1, sizeof(buf1), -1, is->audio.filter_src.channel_layout);
                av_get_channel_layout_string(buf2, sizeof(buf2), -1, dec_channel_layout);
                av_log(NULL, AV_LOG_DEBUG,
                       "Audio frame changed from rate:%d ch:%d fmt:%s layout:%s serial:%d to rate:%d ch:%d fmt:%s layout:%s serial:%d\n",
                       is->audio.filter_src.freq, is->audio.filter_src.channels, av_get_sample_fmt_name(is->audio.filter_src.fmt), buf1, last_serial,
                       frame->sample_rate, frame->channels, av_get_sample_fmt_name((AVSampleFormat)frame->format), buf2, is->audio.decoder.pkt_serial);

                is->audio.filter_src.fmt            = (AVSampleFormat)frame->format;
                is->audio.filter_src.channels       = frame->channels;
                is->audio.filter_src.channel_layout = dec_channel_layout;
                is->audio.filter_src.freq           = frame->sample_rate;
                last_serial                         = is->audio.decoder.pkt_serial;

                if ((ret = is->audio.configure_filters(afilters, 1)) < 0)
                    goto the_end;
            }

            if ((ret = av_buffersrc_add_frame(is->audio.in_filter, frame)) < 0)
                goto the_end;

            while ((ret = av_buffersink_get_frame_flags(is->audio.out_filter, frame, 0)) >= 0) {
                tb = av_buffersink_get_time_base(is->audio.out_filter);
#endif
                if (!(af = is->audio.frames.peek_writeable()))
                    goto the_end;

                af->pts = (frame->pts == AV_NOPTS_VALUE) ? NAN : frame->pts * av_q2d(tb);
                af->pos = frame->pkt_pos;
                af->serial = is->audio.decoder.pkt_serial;
                af->duration = av_q2d((AVRational){frame->nb_samples, frame->sample_rate});

                av_frame_move_ref(af->frame, frame);
                is->audio.frames.push();

#if CONFIG_AVFILTER
                if (is->audio.packets.serial != is->audio.decoder.pkt_serial)
                    break;
            }
            if (ret == AVERROR_EOF)
                is->audio.decoder.finished = is->audio.decoder.pkt_serial;
#endif
        }
    } while (ret >= 0 || ret == AVERROR(EAGAIN) || ret == AVERROR_EOF);
the_end:
#if CONFIG_AVFILTER
    avfilter_graph_free(&is->audio.graph);
#endif
    av_frame_free(&frame);
    return ret;
}

static int video_thread(void *arg)
{
    HVideoState *is = static_cast<HVideoState *>(arg);
    AVFrame *frame = av_frame_alloc();
    double pts;
    double duration;
    int ret;
    AVRational tb = is->video.stream->time_base;
    AVRational frame_rate = av_guess_frame_rate(is->ic, is->video.stream, NULL);

#if CONFIG_AVFILTER
    AVFilterGraph *graph = NULL;
    AVFilterContext *filt_out = NULL, *filt_in = NULL;
    int last_w = 0;
    int last_h = 0;
    AVPixelFormat last_format = AV_PIX_FMT_NONE;
    int last_serial = -1;
    int last_vfilter_idx = 0;
#endif

    if (!frame)
        return AVERROR(ENOMEM);

    for (;;) {
        ret = is->get_video_frame(frame);
        if (ret < 0)
            goto the_end;
        if (!ret)
            continue;

#if CONFIG_AVFILTER
        if (   last_w != frame->width
            || last_h != frame->height
            || last_format != frame->format
            || last_serial != is->video.decoder.pkt_serial
            || last_vfilter_idx != is->vfilter_idx) {
            av_log(NULL, AV_LOG_DEBUG,
                   "Video frame changed from size:%dx%d format:%s serial:%d to size:%dx%d format:%s serial:%d\n",
                   last_w, last_h,
                   (const char *)av_x_if_null(av_get_pix_fmt_name(last_format), "none"), last_serial,
                   frame->width, frame->height,
                   (const char *)av_x_if_null(av_get_pix_fmt_name((AVPixelFormat)frame->format), "none"), is->video.decoder.pkt_serial);
            avfilter_graph_free(&graph);
            graph = avfilter_graph_alloc();
            if (!graph) {
                ret = AVERROR(ENOMEM);
                goto the_end;
            }
            graph->nb_threads = filter_nbthreads;
            if ((ret = is->configure_video_filters(graph, vfilters_list ? vfilters_list[is->vfilter_idx] : NULL, frame)) < 0) {
                SDL_Event event;
                event.type = FF_QUIT_EVENT;
                event.user.data1 = is;
                SDL_PushEvent(&event);
                goto the_end;
            }
            filt_in  = is->in_video_filter;
            filt_out = is->out_video_filter;
            last_w = frame->width;
            last_h = frame->height;
            last_format = (AVPixelFormat)frame->format;
            last_serial = is->video.decoder.pkt_serial;
            last_vfilter_idx = is->vfilter_idx;
            frame_rate = av_buffersink_get_frame_rate(filt_out);
        }

        ret = av_buffersrc_add_frame(filt_in, frame);
        if (ret < 0)
            goto the_end;

        while (ret >= 0) {
            is->frame_last_returned_time = av_gettime_relative() / 1000000.0;

            ret = av_buffersink_get_frame_flags(filt_out, frame, 0);
            if (ret < 0) {
                if (ret == AVERROR_EOF)
                    is->video.decoder.finished = is->video.decoder.pkt_serial;
                ret = 0;
                break;
            }

            is->frame_last_filter_delay = av_gettime_relative() / 1000000.0 - is->frame_last_returned_time;
            if (fabs(is->frame_last_filter_delay) > AV_SYNC_THRESHOLD_NO / 10.0)
                is->frame_last_filter_delay = 0;
            tb = av_buffersink_get_time_base(filt_out);
#endif
            duration = (frame_rate.num && frame_rate.den ? av_q2d((AVRational){frame_rate.den, frame_rate.num}) : 0);
            pts = (frame->pts == AV_NOPTS_VALUE) ? NAN : frame->pts * av_q2d(tb);
            ret = is->queue_picture(frame, pts, duration, frame->pkt_pos, is->video.decoder.pkt_serial);
            av_frame_unref(frame);
#if CONFIG_AVFILTER
            if (is->video.packets.serial != is->video.decoder.pkt_serial)
                break;
        }
#endif

        if (ret < 0)
            goto the_end;
    }
the_end:
#if CONFIG_AVFILTER
    avfilter_graph_free(&graph);
#endif
    av_frame_free(&frame);
    return 0;
}

int subtitle_thread(void *arg)
{
    HVideoState *is = static_cast<HVideoState *>(arg);
    HFrame *sp;
    int got_subtitle;
    double pts;

    for (;;) {
        if (!(sp = is->subtitle.frames.peek_writeable()))
            return 0;

        if ((got_subtitle = is->subtitle.decoder.decode(NULL, &sp->sub)) < 0)
            break;

        pts = 0;

        if (got_subtitle && sp->sub.format == 0) {
            if (sp->sub.pts != AV_NOPTS_VALUE)
                pts = sp->sub.pts / (double)AV_TIME_BASE;
            sp->pts = pts;
            sp->serial = is->subtitle.decoder.pkt_serial;
            sp->width = is->subtitle.decoder.avctx->width;
            sp->height = is->subtitle.decoder.avctx->height;
            sp->uploaded = 0;

            /* now we can update the picture count */
            is->subtitle.frames.push();
        } else if (got_subtitle) {
            avsubtitle_free(&sp->sub);
        }
    }
    return 0;
}

/* this thread gets the stream from the disk or the network */
int read_thread(void *arg)
{
    int i, ret, pkt_ts;
    int st_index[AVMEDIA_TYPE_NB];
    int64_t stream_start_time;
    bool scan_all_pmts_set = false;
    bool pkt_in_play_range = false;
    auto is = static_cast<HVideoState *>(arg);
    auto ic = avformat_alloc_context();
    auto pkt = av_packet_alloc();
    auto wait_mutex = SDL_CreateMutex();
    AVDictionaryEntry *t;

    try
    {
        if (!wait_mutex)
            throw av_asprintf("SDL_CreateMutex(): %s", SDL_GetError());

        if (!ic)
            throw "Could not allocate context.";
        ic->interrupt_callback.callback = decode_interrupt;
        ic->interrupt_callback.opaque = is;
        if (!av_dict_get(format_opts, "scan_all_pmts", nullptr, AV_DICT_MATCH_CASE))
        {
            av_dict_set(&format_opts, "scan_all_pmts", "1", AV_DICT_DONT_OVERWRITE);
            scan_all_pmts_set = true;
        }
        if (avformat_open_input(&ic, is->filename, is->iformat, &format_opts) < 0)
            throw "Could not open input stream.";
        if (scan_all_pmts_set)
            av_dict_set(&format_opts, "scan_all_pmts", nullptr, AV_DICT_MATCH_CASE);
        if ((t = av_dict_get(format_opts, "", nullptr, AV_DICT_IGNORE_SUFFIX)))
            throw av_asprintf("Option %s not found.", t->key);
        if (genpts)
            ic->flags |= AVFMT_FLAG_GENPTS;
        av_format_inject_global_side_data(ic);
        if (find_stream_info)
        {
            auto opts = setup_find_stream_info_opts(ic, codec_opts);
            auto orig_nb_streams = ic->nb_streams;
            ret = avformat_find_stream_info(ic, opts);
            for (i = 0; i < orig_nb_streams; i++)
                av_dict_free(&opts[i]);
            av_freep(&opts);
            if (ret < 0)
                throw av_asprintf("%s: could not find codec parameters.", is->filename);
        }
        if (ic->pb)
            ic->pb->eof_reached = 0; // FIXME hack, ffplay maybe should not use avio_feof() to test for the end

        if (seek_by_bytes < 0)
            seek_by_bytes = !!(ic->iformat->flags & AVFMT_TS_DISCONT) && strcmp("ogg", ic->iformat->name);

        is->ic = ic;
        is->eof = 0;
        is->max_frame_duration = (ic->iformat->flags & AVFMT_TS_DISCONT) ? 10.0 : 3600.0;
        is->realtime = is_realtime(ic);
        is->show_mode = show_mode;

        if (!window_title && (t = av_dict_get(ic->metadata, "title", nullptr, 0)))
            window_title = av_asprintf("%s - %s", t->value, input_filename);

        /* if seeking requested, we execute it */
        if (start_time != AV_NOPTS_VALUE)
        {
            auto timestamp = start_time;
            /* add the stream start time */
            if (ic->start_time != AV_NOPTS_VALUE)
                timestamp += ic->start_time;
            if (avformat_seek_file(ic, -1, INT64_MIN, timestamp, INT64_MAX, 0) < 0)
                av_log(nullptr, AV_LOG_WARNING, "%s: could not seek to position %0.3f\n", is->filename, 1.0 * timestamp / AV_TIME_BASE);
        }

        if (show_status)
            av_dump_format(ic, 0, is->filename, 0);

        memset(st_index, -1, sizeof(st_index));
        for (i = 0; i < ic->nb_streams; i++)
        {
            auto st = ic->streams[i];
            auto type = st->codecpar->codec_type;
            st->discard = AVDISCARD_ALL;
            if (type >= 0 && wanted_stream_spec[type] && st_index[type] == -1)
                if (avformat_match_stream_specifier(ic, st, wanted_stream_spec[type]) > 0)
                    st_index[type] = i;
        }
        for (i = 0; i < AVMEDIA_TYPE_NB; i++)
        {
            if (wanted_stream_spec[i] && st_index[i] == -1)
            {
                av_log(nullptr, AV_LOG_ERROR, "Stream specifier %s does not match any %s stream\n", wanted_stream_spec[i], av_get_media_type_string((AVMediaType)i));
                st_index[i] = INT_MAX;
            }
        }
        if (!video_disable)
            st_index[AVMEDIA_TYPE_VIDEO] = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, st_index[AVMEDIA_TYPE_VIDEO], -1, nullptr, 0);
        if (!audio_disable)
            st_index[AVMEDIA_TYPE_AUDIO] = av_find_best_stream(ic, AVMEDIA_TYPE_AUDIO, st_index[AVMEDIA_TYPE_AUDIO], st_index[AVMEDIA_TYPE_VIDEO], nullptr, 0);
        if (!video_disable && !subtitle_disable)
            st_index[AVMEDIA_TYPE_SUBTITLE] = av_find_best_stream(ic, AVMEDIA_TYPE_SUBTITLE, st_index[AVMEDIA_TYPE_SUBTITLE], (st_index[AVMEDIA_TYPE_AUDIO] >= 0 ? st_index[AVMEDIA_TYPE_AUDIO] : st_index[AVMEDIA_TYPE_VIDEO]), nullptr, 0);

        if (st_index[AVMEDIA_TYPE_VIDEO] >= 0)
        {
            auto st = ic->streams[st_index[AVMEDIA_TYPE_VIDEO]];
            auto codecpar = st->codecpar;
            auto sar = av_guess_sample_aspect_ratio(ic, st, nullptr);
            if (codecpar->width)
                set_default_window_size(codecpar->width, codecpar->height, sar);
        }

        /* open the streams */
        if (st_index[AVMEDIA_TYPE_AUDIO] >= 0)
            is->audio.open_stream(st_index[AVMEDIA_TYPE_AUDIO], ic, audio_codec_name);
        if (st_index[AVMEDIA_TYPE_VIDEO] >= 0)
            ret = is->video.open_stream(st_index[AVMEDIA_TYPE_VIDEO], ic, video_codec_name);
        if (is->show_mode == SHOW_MODE_NONE)
            is->show_mode = ret >= 0 ? SHOW_MODE_VIDEO : SHOW_MODE_RDFT;
        if (st_index[AVMEDIA_TYPE_SUBTITLE] >= 0)
            is->subtitle.open_stream(st_index[AVMEDIA_TYPE_SUBTITLE], ic, subtitle_codec_name);

        if (is->video.stream_index < 0 && is->audio.stream_index < 0)
            av_asprintf("Failed to open file '%s' or configure filtergraph.", is->filename);

        if (infinite_buffer < 0 && is->realtime)
            infinite_buffer = 1;

        for (;;)
        {
            if (is->abort_request)
                break;
            if (is->paused != is->last_paused)
            {
                is->last_paused = is->paused;
                if (is->paused)
                    is->read_pause_return = av_read_pause(ic);
                else
                    av_read_play(ic);
            }
            #if CONFIG_RTSP_DEMUXER || CONFIG_MMSH_PROTOCOL
            if (is->paused && (!strcmp(ic->iformat->name, "rtsp") || (ic->pb && !strncmp(input_filename, "mmsh:", 5))))
            {
                /* wait 10 ms to avoid trying to get another packet */
                /* XXX: horrible */
                SDL_Delay(10);
                continue;
            }
            #endif
            if (is->seek_req)
            {
                // FIXME the +-2 is due to rounding being not done in the correct direction in generation of the seek_pos/seek_rel variables
                auto seek_target = is->seek_pos;
                auto seek_min    = is->seek_rel > 0 ? seek_target - is->seek_rel + 2: INT64_MIN;
                auto seek_max    = is->seek_rel < 0 ? seek_target - is->seek_rel - 2: INT64_MAX;

                if (avformat_seek_file(is->ic, -1, seek_min, seek_target, seek_max, is->seek_flags) < 0)
                {
                    av_log(nullptr, AV_LOG_ERROR, "%s: error while seeking\n", is->ic->url);
                }
                else
                {
                    if (is->audio.stream_index >= 0)
                    {
                        is->audio.packets.flush();
                        is->audio.packets.put(&flush_pkt);
                    }
                    if (is->subtitle.stream_index >= 0)
                    {
                        is->subtitle.packets.flush();
                        is->subtitle.packets.put(&flush_pkt);
                    }
                    if (is->video.stream_index >= 0)
                    {
                        is->video.packets.flush();
                        is->video.packets.put(&flush_pkt);
                    }
                    if (is->seek_flags & AVSEEK_FLAG_BYTE)
                        is->extclk.set_clock(NAN, 0);
                    else
                        is->extclk.set_clock(seek_target / (double)AV_TIME_BASE, 0);
                }
                is->seek_req = 0;
                is->queue_attachments_req = 1;
                is->eof = 0;
                if (is->paused)
                    is->step_to_next_frame();
            }
            if (is->queue_attachments_req)
            {
                if (is->video.stream && is->video.stream->disposition & AV_DISPOSITION_ATTACHED_PIC)
                {
                    AVPacket copy;
                    if (av_packet_ref(&copy, &is->video.stream->attached_pic) < 0)
                        throw "Could not copy attached packet";
                    is->video.packets.put(&copy);
                    is->video.packets.put(is->video.stream_index);
                }
                is->queue_attachments_req = 0;
            }

            /* if the queue are full, no need to read more */
            if (infinite_buffer < 1 &&
                (is->audio.packets.size + is->video.packets.size + is->subtitle.packets.size > MAX_QUEUE_SIZE
                 || (is->stream_has_enough_packets(is->audio.stream, is->audio.stream_index, &is->audio.packets) &&
                     is->stream_has_enough_packets(is->video.stream, is->video.stream_index, &is->video.packets) &&
                     is->stream_has_enough_packets(is->subtitle.stream, is->subtitle.stream_index, &is->subtitle.packets))))
            {
                /* wait 10 ms */
                SDL_LockMutex(wait_mutex);
                SDL_CondWaitTimeout(is->continue_read_thread, wait_mutex, 10);
                SDL_UnlockMutex(wait_mutex);
                continue;
            }

            if (!is->paused &&
                (!is->audio.stream || (is->audio.decoder.finished == is->audio.packets.serial && is->audio.frames.remaining() == 0)) &&
                (!is->video.stream || (is->video.decoder.finished == is->video.packets.serial && is->video.frames.remaining() == 0)))
            {
                if (loop != 1 && (!loop || --loop))
                    is->seek(start_time != AV_NOPTS_VALUE ? start_time : 0, 0, 0);
                else if (autoexit)
                    throw "Auto exit";
            }
            ret = av_read_frame(ic, pkt);
            if (ret < 0)
            {
                if ((ret == AVERROR_EOF || avio_feof(ic->pb)) && !is->eof)
                {
                    if (is->video.stream_index >= 0)
                        is->video.packets.put(is->video.stream_index);
                    if (is->audio.stream_index >= 0)
                        is->audio.packets.put(is->audio.stream_index);
                    if (is->subtitle.stream_index >= 0)
                        is->subtitle.packets.put(is->subtitle.stream_index);
                    is->eof = 1;
                }
                if (ic->pb && ic->pb->error)
                    break;
                SDL_LockMutex(wait_mutex);
                SDL_CondWaitTimeout(is->continue_read_thread, wait_mutex, 10);
                SDL_UnlockMutex(wait_mutex);
                continue;
            }
            else
            {
                is->eof = 0;
            }
            /* check if packet is in play range specified by user, then queue, otherwise discard */
            stream_start_time = ic->streams[pkt->stream_index]->start_time;
            pkt_ts = pkt->pts == AV_NOPTS_VALUE ? pkt->dts : pkt->pts;
            pkt_in_play_range = duration == AV_NOPTS_VALUE ||
                                (pkt_ts - (stream_start_time != AV_NOPTS_VALUE ? stream_start_time : 0)) * av_q2d(ic->streams[pkt->stream_index]->time_base) - (start_time != AV_NOPTS_VALUE ? start_time : 0) / 1000000.0 <= duration / 1000000.0;
            if (pkt->stream_index == is->audio.stream_index && pkt_in_play_range)
                is->audio.packets.put(pkt);
            else if (pkt->stream_index == is->video.stream_index && pkt_in_play_range && !(is->video.stream->disposition & AV_DISPOSITION_ATTACHED_PIC))
                is->video.packets.put(pkt);
            else if (pkt->stream_index == is->subtitle.stream_index && pkt_in_play_range)
                is->subtitle.packets.put(pkt);
            else
                av_packet_unref(pkt);
        }
    }
    catch (char *e)
    {
        av_log(nullptr, AV_LOG_FATAL, "%s\n", e);
        SDL_Event event;
        event.type = FF_QUIT_EVENT;
        event.user.data1 = is;
        SDL_PushEvent(&event);
    }

    av_packet_free(&pkt);
    if (ic && !is->ic)
        avformat_close_input(&ic);
    SDL_DestroyMutex(wait_mutex);
    return 0;
}

void HClock::init(int *queue_serial)
{
    this->speed = 1.0;
    this->paused = 0;
    this->queue_serial = queue_serial;
    set_clock(NAN, -1);
}

void HClock::set_clock(double pts, int serial)
{
    set_clock_at(pts, serial, av_gettime_relative() / 1000000.0);
}

void HClock::set_clock_at(double pts, int serial, double time)
{
    this->pts = pts;
    this->last_updated = time;
    this->pts_drift = pts - time;
    this->serial = serial;
}

void HClock::set_clock_speed(double speed)
{
    set_clock(get_clock(), serial);
    this->speed = speed;
}

void HClock::sync_clock(HClock *slave)
{
    double clock1 = get_clock();
    double clock2 = slave->get_clock();
    if (!isnan(clock2) && (isnan(clock1) || fabs(clock1 - clock2) > AV_SYNC_THRESHOLD_NO))
        set_clock(clock2, slave->serial);
}

double HClock::get_clock()
{
    if (*queue_serial != serial)
        return NAN;
    if (paused)
        return pts;
    auto time = av_gettime_relative() / 1000000.0;
    return pts_drift + time - (time - last_updated) * (1.0 - speed);
}

bool HPacketQueue::init()
{
    mutex = SDL_CreateMutex();
    if (!mutex)
    {
        av_log(nullptr, AV_LOG_FATAL, "SDL_CreateMutex(): %s\n", SDL_GetError());
        return false;
    }
    cond = SDL_CreateCond();
    if (!cond)
    {
        av_log(nullptr, AV_LOG_FATAL, "SDL_CreateCond(): %s\n", SDL_GetError());
        return false;
    }
    abort_request = 1;
    return true;
}

int HPacketQueue::put(AVPacket *pkt)
{
    int ret;
    SDL_LockMutex(mutex);
    ret = put_private(pkt);
    SDL_UnlockMutex(mutex);

    if (pkt != &flush_pkt && ret < 0)
        av_packet_unref(pkt);
    return ret;
}

int HPacketQueue::put(int index)
{
    AVPacket pkt1, *pkt = &pkt1;
    av_init_packet(pkt);
    pkt->data = nullptr;
    pkt->size = 0;
    pkt->stream_index = index;
    return put(pkt);
}

int HPacketQueue::put_private(AVPacket *pkt)
{
    HPacketList *pkt1;

    if (abort_request)
        return -1;

    pkt1 = (HPacketList *)av_malloc(sizeof(HPacketList));
    if (!pkt1)
        return -1;
    if (pkt == &flush_pkt)
        serial++;
    pkt1->pkt = *pkt;
    pkt1->next = nullptr;
    pkt1->serial = serial;
    if (!last_pkt)
        first_pkt = pkt1;
    else
        last_pkt->next = pkt1;
    last_pkt = pkt1;
    nb_packets++;
    size += pkt1->pkt.size + sizeof(*pkt1);
    duration += pkt1->pkt.duration;
    /* XXX: should duplicate packet data in DV case */
    SDL_CondSignal(cond);
    return 0;
}

/* return < 0 if aborted, 0 if no packet and > 0 if packet.  */
int HPacketQueue::get(AVPacket *pkt, int block, int *serial)
{
    HPacketList *pkt1;
    int ret;

    SDL_LockMutex(mutex);

    for (;;)
    {
        if (abort_request)
        {
            ret = -1;
            break;
        }

        pkt1 = first_pkt;
        if (pkt1)
        {
            first_pkt = pkt1->next;
            if (!first_pkt)
                last_pkt = nullptr;
            nb_packets--;
            size -= pkt1->pkt.size + sizeof(*pkt1);
            duration -= pkt1->pkt.duration;
            *pkt = pkt1->pkt;
            if (serial)
                *serial = pkt1->serial;
            av_free(pkt1);
            ret = 1;
            break;
        }
        else if (!block)
        {
            ret = 0;
            break;
        }
        else
        {
            SDL_CondWait(cond, mutex);
        }
    }
    SDL_UnlockMutex(mutex);
    return ret;
}

void HPacketQueue::flush()
{
    HPacketList *pkt, *pkt1;

    SDL_LockMutex(mutex);
    for (pkt = first_pkt; pkt; pkt = pkt1)
    {
        pkt1 = pkt->next;
        av_packet_unref(&pkt->pkt);
        av_freep(&pkt);
    }
    last_pkt = nullptr;
    first_pkt = nullptr;
    nb_packets = 0;
    size = 0;
    duration = 0;
    SDL_UnlockMutex(mutex);
}

void HPacketQueue::start()
{
    SDL_LockMutex(mutex);
    abort_request = 0;
    put_private(&flush_pkt);
    SDL_UnlockMutex(mutex);
}

void HPacketQueue::abort()
{
    SDL_LockMutex(mutex);
    abort_request = 1;
    SDL_CondSignal(cond);
    SDL_UnlockMutex(mutex);
}

void HPacketQueue::destroy()
{
    flush();
    SDL_DestroyMutex(mutex);
    SDL_DestroyCond(cond);
}

bool HFrameQueue::init(HPacketQueue *pktq, int max_size, bool keep_last)
{
    int i;
    this->mutex = SDL_CreateMutex();
    if (!this->mutex)
    {
        av_log(nullptr, AV_LOG_FATAL, "SDL_CreateMutex(): %s\n", SDL_GetError());
        return false;
    }
    this->cond = SDL_CreateCond();
    if (!this->cond)
    {
        av_log(nullptr, AV_LOG_FATAL, "SDL_CreateCond(): %s\n", SDL_GetError());
        return false;
    }
    this->pktq = pktq;
    this->max_size = FFMIN(max_size, FRAME_QUEUE_SIZE);
    this->keep_last = keep_last;
    for (i = 0; i < this->max_size; i++)
        if (!(this->queue[i].frame = av_frame_alloc()))
            return false;
    return true;
}

/* return the number of undisplayed frames in the queue */
int HFrameQueue::remaining()
{
    return size - rindex_shown;
}

/* return last shown position */
int64_t HFrameQueue::last_pos()
{
    auto fp = &queue[rindex];
    return rindex_shown && fp->serial == pktq->serial ? fp->pos : -1;
}

void HFrameQueue::unref_item(HFrame *vp)
{
    av_frame_unref(vp->frame);
    avsubtitle_free(&vp->sub);
}

HFrame *HFrameQueue::peek()
{
    return &queue[(rindex + rindex_shown) % max_size];
}

HFrame *HFrameQueue::peek_next()
{
    return &queue[(rindex + rindex_shown + 1) % max_size];
}

HFrame *HFrameQueue::peek_last()
{
    return &queue[rindex];
}

HFrame *HFrameQueue::peek_writeable()
{
    /* wait until we have space to put a new frame */
    SDL_LockMutex(mutex);
    while (size >= max_size && !pktq->abort_request)
        SDL_CondWait(cond, mutex);
    SDL_UnlockMutex(mutex);
    return pktq->abort_request ? nullptr : &queue[windex];
}

HFrame *HFrameQueue::peek_readable()
{
    /* wait until we have a readable a new frame */
    SDL_LockMutex(mutex);
    while (size - rindex_shown <= 0 && !pktq->abort_request)
        SDL_CondWait(cond, mutex);
    SDL_UnlockMutex(mutex);
    return pktq->abort_request ? nullptr : &queue[(rindex + rindex_shown) % max_size];
}

void HFrameQueue::push()
{
    if (++windex == max_size)
        windex = 0;
    SDL_LockMutex(mutex);
    size++;
    SDL_CondSignal(cond);
    SDL_UnlockMutex(mutex);
}

void HFrameQueue::next()
{
    if (keep_last && !rindex_shown)
    {
        rindex_shown = 1;
        return;
    }
    unref_item(&queue[rindex]);
    if (++rindex == max_size)
        rindex = 0;
    SDL_LockMutex(mutex);
    size--;
    SDL_CondSignal(cond);
    SDL_UnlockMutex(mutex);
}

void HFrameQueue::signal()
{
    SDL_LockMutex(mutex);
    SDL_CondSignal(cond);
    SDL_UnlockMutex(mutex);
}

void HFrameQueue::destroy()
{
    int i;
    for (i = 0; i < max_size; i++)
    {
        auto vp = &queue[i];
        unref_item(vp);
        av_frame_free(&vp->frame);
    }
    SDL_DestroyMutex(mutex);
    SDL_DestroyCond(cond);
}

void HDecoder::init(HPacketQueue *queue, SDL_cond *empty_queue_cond)
{
    this->queue = queue;
    this->empty_queue_cond = empty_queue_cond;
    this->start_pts = AV_NOPTS_VALUE;
    this->pkt_serial = -1;
}

void HDecoder::set_codec_context(AVCodecContext *avctx)
{
    this->avctx = avctx;
}

int HDecoder::decode(AVFrame *frame, AVSubtitle *sub)
{
    int ret = AVERROR(EAGAIN);

    for (;;)
    {
        AVPacket pkt1;

        if (queue->serial == pkt_serial)
        {
            do {
                if (queue->abort_request)
                    return -1;

                switch (avctx->codec_type)
                {
                case AVMEDIA_TYPE_VIDEO:
                    ret = avcodec_receive_frame(avctx, frame);
                    if (ret >= 0)
                    {
                        if (decoder_reorder_pts == -1)
                            frame->pts = frame->best_effort_timestamp;
                        else if (!decoder_reorder_pts)
                            frame->pts = frame->pkt_dts;
                    }
                    break;
                case AVMEDIA_TYPE_AUDIO:
                    ret = avcodec_receive_frame(avctx, frame);
                    if (ret >= 0)
                    {
                        AVRational tb = (AVRational){1, frame->sample_rate};
                        if (frame->pts != AV_NOPTS_VALUE)
                            frame->pts = av_rescale_q(frame->pts, avctx->pkt_timebase, tb);
                        else if (next_pts != AV_NOPTS_VALUE)
                            frame->pts = av_rescale_q(next_pts, next_pts_tb, tb);
                        if (frame->pts != AV_NOPTS_VALUE)
                        {
                            next_pts = frame->pts + frame->nb_samples;
                            next_pts_tb = tb;
                        }
                    }
                    break;
                default:
                    break;
                }
                if (ret == AVERROR_EOF)
                {
                    finished = pkt_serial;
                    avcodec_flush_buffers(avctx);
                    return 0;
                }
                if (ret >= 0)
                    return 1;
            } while (ret != AVERROR(EAGAIN));
        }

        do {
            if (queue->nb_packets == 0)
                SDL_CondSignal(empty_queue_cond);
            if (packet_pending)
            {
                av_packet_move_ref(&pkt1, &pkt);
                packet_pending = 0;
            }
            else
            {
                if (queue->get(&pkt1, 1, &pkt_serial) < 0)
                    return -1;
            }
            if (queue->serial == pkt_serial)
                break;
            av_packet_unref(&pkt1);
        } while (1);

        if (pkt1.data == flush_pkt.data)
        {
            avcodec_flush_buffers(avctx);
            finished = 0;
            next_pts = start_pts;
            next_pts_tb = start_pts_tb;
        }
        else
        {
            if (avctx->codec_type == AVMEDIA_TYPE_SUBTITLE)
            {
                int got_frame = 0;
                ret = avcodec_decode_subtitle2(avctx, sub, &got_frame, &pkt1);
                if (ret < 0)
                {
                    ret = AVERROR(EAGAIN);
                }
                else
                {
                    if (got_frame && !pkt1.data)
                    {
                        packet_pending = 1;
                        av_packet_move_ref(&pkt, &pkt1);
                    }
                    ret = got_frame ? 0 : (pkt1.data ? AVERROR(EAGAIN) : AVERROR_EOF);
                }
            }
            else
            {
                if (avcodec_send_packet(avctx, &pkt1) == AVERROR(EAGAIN))
                {
                    av_log(avctx, AV_LOG_ERROR, "Receive_frame and send_packet both returned EAGAIN, which is an API violation.\n");
                    packet_pending = 1;
                    av_packet_move_ref(&pkt, &pkt1);
                }
            }
            av_packet_unref(&pkt1);
        }
    }
}

bool HDecoder::start(int (*fn)(void *), const char *thread_name, void *arg)
{
    queue->start();
    decoder_tid = SDL_CreateThread(fn, thread_name, arg);
    if (!decoder_tid)
    {
        av_log(nullptr, AV_LOG_ERROR, "SDL_CreateThread(): %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void HDecoder::abort(HFrameQueue *fq)
{
    queue->abort();
    fq->signal();
    SDL_WaitThread(decoder_tid, nullptr);
    decoder_tid = nullptr;
    queue->flush();
}

void HDecoder::destroy()
{
    av_packet_unref(&pkt);
    avcodec_free_context(&avctx);
}

bool HMediaStream::init(HVideoState *is, int max_size, bool keep_last, SDL_cond *empty_queue_cond)
{
    stream_index = -1;
    stream_last = -1;
    stream = nullptr;
    if (!packets.init())
    {
        av_log(nullptr, AV_LOG_FATAL, "Packet queue init fail.");
        return false;
    }
    if (!frames.init(&packets, max_size, keep_last))
    {
        av_log(nullptr, AV_LOG_FATAL, "Frame queue init fail.");
        return false;
    }
    decoder.init(&packets, empty_queue_cond);
    this->is = is;
    return true;
}

void HMediaStream::destroy()
{
    if (stream_index >= 0)
        close_stream(stream_index);
    packets.destroy();
    frames.destroy();
}

bool HMediaStream::open_stream(int index, AVFormatContext *ic, const char *forced_codec_name)
{
    if (index < 0 || index >= ic->nb_streams)
        return false;

    AVDictionary *opts = nullptr;
    int stream_lowres = lowres;
    auto avctx = avcodec_alloc_context3(nullptr);
    if (!avctx)
        return false;

    try
    {
        if (avcodec_parameters_to_context(avctx, ic->streams[index]->codecpar) < 0)
        {
            av_log(nullptr, AV_LOG_FATAL, "Couldn't set parameters to codec context.\n");
            throw "";
        }
        avctx->pkt_timebase = ic->streams[index]->time_base;

        auto codec = avcodec_find_decoder(avctx->codec_id);
        if (forced_codec_name)
            codec = avcodec_find_decoder_by_name(forced_codec_name);
        if (!codec)
        {
            if (forced_codec_name)
                av_log(nullptr, AV_LOG_FATAL, "No codec could be found with name '%s'\n", forced_codec_name);
            else
                av_log(nullptr, AV_LOG_FATAL, "No decoder could be found for codec %s\n", avcodec_get_name(avctx->codec_id));
            throw "";
        }
        avctx->codec_id = codec->id;

        if (stream_lowres > codec->max_lowres)
        {
            av_log(avctx, AV_LOG_WARNING, "The maximum value for lowres supported by the decoder is %d\n", codec->max_lowres);
            stream_lowres = codec->max_lowres;
        }
        avctx->lowres = stream_lowres;

        if (fast)
            avctx->flags2 |= AV_CODEC_FLAG2_FAST;

        auto opts = filter_codec_opts(codec_opts, avctx->codec_id, ic, ic->streams[index], codec);
        if (!av_dict_get(opts, "threads", nullptr, 0))
            av_dict_set(&opts, "threads", "auto", 0);
        if (stream_lowres)
            av_dict_set_int(&opts, "lowres", stream_lowres, 0);
        if (avctx->codec_type == AVMEDIA_TYPE_VIDEO || avctx->codec_type == AVMEDIA_TYPE_AUDIO)
            av_dict_set(&opts, "refcounted_frames", "1", 0);

        if (avcodec_open2(avctx, codec, &opts) < 0)
        {
            av_log(nullptr, AV_LOG_FATAL, "Couldn't open codec");
            throw "";
        }

        if (auto t = av_dict_get(opts, "", nullptr, AV_DICT_IGNORE_SUFFIX))
        {
            av_log(nullptr, AV_LOG_ERROR, "Option %s not found.\n", t->key);
            throw "";
        }

        ic->streams[index]->discard = AVDISCARD_DEFAULT;
        decoder.set_codec_context(avctx);
        if (!open_else(avctx))
            throw "";
        eof = 0;
        stream_last = index;
        stream_index = index;
        stream = ic->streams[index];
        this->ic = ic;
    }
    catch (...)
    {
        avcodec_free_context(&avctx);
        return false;
    }
    av_dict_free(&opts);
    return true;
}

void HMediaStream::close_stream(uint index)
{
    if (index < 0 || index >= ic->nb_streams)
        return;
    close_else();
    ic->streams[index]->discard = AVDISCARD_ALL;
    stream = nullptr;
    stream_index = -1;
}

bool HVideoStream::open_else(AVCodecContext *avctx)
{
    if (!decoder.start(video_thread, "video_decoder", is))
        return false;
    queue_attachments_req = 1;
    return true;
}

void HVideoStream::close_else()
{
    decoder.abort(&frames);
    decoder.destroy();
}

bool HAudioStream::open_else(AVCodecContext *avctx)
{
    int sample_rate, nb_channels;
    int64_t channel_layout;

#if CONFIG_AVFILTER
        filter_src.freq           = avctx->sample_rate;
        filter_src.channels       = avctx->channels;
        filter_src.channel_layout = get_valid_channel_layout(avctx->channel_layout, avctx->channels);
        filter_src.fmt            = avctx->sample_fmt;
        if (configure_filters(afilters, 0) < 0)
            return false;
        auto sink = out_filter;
        sample_rate    = av_buffersink_get_sample_rate(sink);
        nb_channels    = av_buffersink_get_channels(sink);
        channel_layout = av_buffersink_get_channel_layout(sink);
#else
    sample_rate    = avctx->sample_rate;
    nb_channels    = avctx->channels;
    channel_layout = avctx->channel_layout;
#endif

    /* prepare audio output */
    int ret;
    if ((ret = audio_open(this, channel_layout, nb_channels, sample_rate, &tgt)) < 0)
        return false;
    hw_buf_size = ret;
    src = tgt;
    buf_size  = 0;
    buf_index = 0;

    /* init averaging filter */
    diff_avg_coef  = exp(log(0.01) / AUDIO_DIFF_AVG_NB);
    diff_avg_count = 0;
    /* since we do not have a precise anough audio FIFO fullness,
               we correct audio sync only if larger than this threshold */
    diff_threshold = 1.0 * hw_buf_size / tgt.bytes_per_sec;



    if ((ic->iformat->flags & (AVFMT_NOBINSEARCH | AVFMT_NOGENSEARCH | AVFMT_NO_BYTE_SEEK)) && !ic->iformat->read_seek)
    {
        decoder.start_pts = stream->start_time;
        decoder.start_pts_tb = stream->time_base;
    }
    if (!decoder.start(audio_thread, "audio_decoder", is))
        return false;
    SDL_PauseAudioDevice(audio_dev, 0);
    return true;
}

int HAudioStream::configure_filters(const char *afilters, int force_output_format)
{
    static const AVSampleFormat sample_fmts[] = { AV_SAMPLE_FMT_S16, AV_SAMPLE_FMT_NONE };
    int sample_rates[2] = { 0, -1 };
    int64_t channel_layouts[2] = { 0, -1 };
    int channels[2] = { 0, -1 };
    AVFilterContext *filt_asrc = nullptr, *filt_asink = nullptr;
    char aresample_swr_opts[512] = "";
    AVDictionaryEntry *e = nullptr;
    char asrc_args[256];
    int ret;

    avfilter_graph_free(&graph);
    if (!(graph = avfilter_graph_alloc()))
        return AVERROR(ENOMEM);
    graph->nb_threads = filter_nbthreads;

    while ((e = av_dict_get(swr_opts, "", e, AV_DICT_IGNORE_SUFFIX)))
        av_strlcatf(aresample_swr_opts, sizeof(aresample_swr_opts), "%s=%s:", e->key, e->value);
    if (strlen(aresample_swr_opts))
        aresample_swr_opts[strlen(aresample_swr_opts)-1] = '\0';
    av_opt_set(graph, "aresample_swr_opts", aresample_swr_opts, 0);

    ret = snprintf(asrc_args, sizeof(asrc_args),
                   "sample_rate=%d:sample_fmt=%s:channels=%d:time_base=%d/%d",
                   filter_src.freq, av_get_sample_fmt_name(filter_src.fmt),
                   filter_src.channels,
                   1, filter_src.freq);
    if (filter_src.channel_layout)
        snprintf(asrc_args + ret, sizeof(asrc_args) - ret, ":channel_layout=0x%ld",  filter_src.channel_layout);

    ret = avfilter_graph_create_filter(&filt_asrc,
                                       avfilter_get_by_name("abuffer"), "ffplay_abuffer",
                                       asrc_args, NULL, graph);
    if (ret < 0)
        goto end;


    ret = avfilter_graph_create_filter(&filt_asink,
                                       avfilter_get_by_name("abuffersink"), "ffplay_abuffersink",
                                       NULL, NULL, graph);
    if (ret < 0)
        goto end;

    if ((ret = av_opt_set_int_list(filt_asink, "sample_fmts", sample_fmts,  AV_SAMPLE_FMT_NONE, AV_OPT_SEARCH_CHILDREN)) < 0)
        goto end;
    if ((ret = av_opt_set_int(filt_asink, "all_channel_counts", 1, AV_OPT_SEARCH_CHILDREN)) < 0)
        goto end;

    if (force_output_format)
    {
        channel_layouts[0] = tgt.channel_layout;
        channels       [0] = tgt.channels;
        sample_rates   [0] = tgt.freq;
        if ((ret = av_opt_set_int(filt_asink, "all_channel_counts", 0, AV_OPT_SEARCH_CHILDREN)) < 0)
            goto end;
        if ((ret = av_opt_set_int_list(filt_asink, "channel_layouts", channel_layouts,  -1, AV_OPT_SEARCH_CHILDREN)) < 0)
            goto end;
        if ((ret = av_opt_set_int_list(filt_asink, "channel_counts" , channels       ,  -1, AV_OPT_SEARCH_CHILDREN)) < 0)
            goto end;
        if ((ret = av_opt_set_int_list(filt_asink, "sample_rates"   , sample_rates   ,  -1, AV_OPT_SEARCH_CHILDREN)) < 0)
            goto end;
    }

    if ((ret = configure_filtergraph(graph, afilters, filt_asrc, filt_asink)) < 0)
        goto end;

    in_filter  = filt_asrc;
    out_filter = filt_asink;

end:
    if (ret < 0)
        avfilter_graph_free(&graph);
    return ret;
}

void HAudioStream::close_else()
{
    decoder.abort(&frames);
    SDL_CloseAudioDevice(audio_dev);
    decoder.destroy();
    swr_free(&swr_ctx);
    av_freep(&buf1);
    buf1_size = 0;
    buf = nullptr;
    if (rdft)
    {
        av_rdft_end(rdft);
        av_freep(&rdft_data);
        rdft = nullptr;
        rdft_bits = 0;
    }
}

bool HSubtitleStream::open_else(AVCodecContext *avctx)
{
    if (!decoder.start(subtitle_thread, "subtitle_thread", is))
        return false;
    return true;
}

void HSubtitleStream::close_else()
{
    decoder.abort(&frames);
    decoder.destroy();
}

bool HVideoState::init(const char *filename, AVInputFormat *iformat)
{
    try
    {
        this->filename = av_strdup(filename);
        if (!this->filename)
        {
            av_log(nullptr, AV_LOG_FATAL, "Input file is empty.");
            return false;
        }
        this->iformat = iformat;

        continue_read_thread = SDL_CreateCond();
        if (!continue_read_thread)
        {
            av_log(nullptr, AV_LOG_FATAL, "SDL_CreateCond(): %s", SDL_GetError());
            throw "";
        }

        if (!video.init(this, VIDEO_QUEUE_SIZE, true, continue_read_thread) ||
            !audio.init(this, SAMPLE_QUEUE_SIZE, true, continue_read_thread) ||
            !subtitle.init(this, SUBPICTURE_QUEUE_SIZE, false, continue_read_thread))
        {
            av_log(nullptr, AV_LOG_FATAL, "Can't open media stream.");
            throw "";
        }
        ytop = 0;
        xleft = 0;

        vidclk.init(&video.packets.serial);
        audclk.init(&audio.packets.serial);
        extclk.init(&extclk.serial);
        audio_clock_serial = -1;
        startup_volume = av_clip(startup_volume, 0, 100);
        startup_volume = av_clip(SDL_MIX_MAXVOLUME * startup_volume / 100, 0, SDL_MIX_MAXVOLUME);
        audio_volume = startup_volume;
        muted = 0;
        sync_mode = av_sync_type;
        read_tid = SDL_CreateThread(read_thread, "read_thread", this);
        if (!read_tid)
        {
            av_log(nullptr, AV_LOG_FATAL, "SDL_CreateThread(): %s\n", SDL_GetError());
            throw "";
        }
        return true;
    }
    catch (...)
    {
        destroy();
        return false;
    }
}

void HVideoState::destroy()
{
    abort_request = 1;
    if (read_tid)
        SDL_WaitThread(read_tid, nullptr);

    video.destroy();
    audio.destroy();
    subtitle.destroy();

    avformat_close_input(&ic);

    SDL_DestroyCond(continue_read_thread);
    sws_freeContext(img_convert_ctx);
    sws_freeContext(sub_convert_ctx);
    av_free(filename);
    if (vis_texture)
        SDL_DestroyTexture(vis_texture);
    if (vid_texture)
        SDL_DestroyTexture(vid_texture);
    if (sub_texture)
        SDL_DestroyTexture(sub_texture);
}

int HVideoState::stream_has_enough_packets(AVStream *st, int stream_id, HPacketQueue *queue)
{
    return stream_id < 0 ||
           queue->abort_request ||
           (st->disposition & AV_DISPOSITION_ATTACHED_PIC) ||
           (queue->nb_packets > MIN_FRAMES && (!queue->duration || av_q2d(st->time_base) * queue->duration > 1.0));
}

int HVideoState::get_master_sync_type()
{
    if (sync_mode == SYNC_VIDEO_MASTER)
        return video.stream ? SYNC_VIDEO_MASTER : SYNC_AUDIO_MASTER;
    if (sync_mode == SYNC_AUDIO_MASTER)
        return audio.stream ? SYNC_AUDIO_MASTER : SYNC_EXTERNAL_CLOCK;
    return SYNC_EXTERNAL_CLOCK;
}

/* get the current master clock value */
double HVideoState::get_master_clock()
{
    auto type = get_master_sync_type();
    if (type == SYNC_VIDEO_MASTER)
        return vidclk.get_clock();
    if (type == SYNC_AUDIO_MASTER)
        return audclk.get_clock();
    return extclk.get_clock();
}

void HVideoState::check_external_clock_speed()
{
    if ((video.stream_index >= 0 && video.packets.nb_packets <= EXTERNAL_CLOCK_MIN_FRAMES) ||
        (audio.stream_index >= 0 && audio.packets.nb_packets <= EXTERNAL_CLOCK_MIN_FRAMES))
    {
        extclk.set_clock_speed(FFMAX(EXTERNAL_CLOCK_SPEED_MIN, extclk.speed - EXTERNAL_CLOCK_SPEED_STEP));
    }
    else if ((video.stream_index < 0 || video.packets.nb_packets > EXTERNAL_CLOCK_MAX_FRAMES) &&
             (audio.stream_index < 0 || audio.packets.nb_packets > EXTERNAL_CLOCK_MAX_FRAMES))
    {
        extclk.set_clock_speed(FFMIN(EXTERNAL_CLOCK_SPEED_MAX, extclk.speed + EXTERNAL_CLOCK_SPEED_STEP));
    }
    else
    {
        double speed = extclk.speed;
        if (speed != 1.0)
            extclk.set_clock_speed(speed + EXTERNAL_CLOCK_SPEED_STEP * (1.0 - speed) / fabs(1.0 - speed));
    }
}

double HVideoState::vp_duration(HFrame *vp, HFrame *nextvp)
{
    if (vp->serial == nextvp->serial)
    {
        double duration = nextvp->pts - vp->pts;
        if (isnan(duration) || duration <= 0 || duration > max_frame_duration)
            return vp->duration;
        return duration;
    }
    return 0.0;
}

double HVideoState::compute_target_delay(double delay)
{
    double sync_threshold, diff = 0;

    /* update delay to follow master synchronisation source */
    if (get_master_sync_type() != SYNC_VIDEO_MASTER)
    {
        /* if video is slave, we try to correct big delays by
           duplicating or deleting a frame */
        diff = vidclk.get_clock() - get_master_clock();

        /* skip or repeat frame. We take into account the
           delay to compute the threshold. I still don't know
           if it is the best guess */
        sync_threshold = FFMAX(AV_SYNC_THRESHOLD_MIN, FFMIN(AV_SYNC_THRESHOLD_MAX, delay));
        if (!isnan(diff) && fabs(diff) < max_frame_duration)
        {
            if (diff <= -sync_threshold)
                delay = FFMAX(0, delay + diff);
            else if (diff >= sync_threshold && delay > AV_SYNC_FRAMEDUP_THRESHOLD)
                delay = delay + diff;
            else if (diff >= sync_threshold)
                delay = 2 * delay;
        }
    }

    av_log(NULL, AV_LOG_TRACE, "video: delay=%0.3f A-V=%f\n",
           delay, -diff);

    return delay;
}

int HVideoState::audio_decode_frame()
{
    int data_size, resampled_data_size;
    int64_t dec_channel_layout;
    av_unused double audio_clock0;
    int wanted_nb_samples;
    HFrame *af;

    if (paused)
        return -1;

    do {
#if defined(_WIN32)
        while (audio.frames.remaining() == 0)
        {
            if ((av_gettime_relative() - audio_callback_time) > 1000000LL * audio.hw_buf_size / audio.tgt.bytes_per_sec / 2)
                return -1;
            av_usleep (1000);
        }
#endif
        if (!(af = audio.frames.peek_readable()))
            return -1;
        audio.frames.next();
    } while (af->serial != audio.packets.serial);

    data_size = av_samples_get_buffer_size(NULL, af->frame->channels,
                                           af->frame->nb_samples,
                                           (AVSampleFormat)af->frame->format, 1);

    dec_channel_layout = (af->frame->channel_layout && af->frame->channels == av_get_channel_layout_nb_channels(af->frame->channel_layout)) ? af->frame->channel_layout : av_get_default_channel_layout(af->frame->channels);
    wanted_nb_samples = synchronize_audio(af->frame->nb_samples);

    if (af->frame->format        != audio.src.fmt            ||
        dec_channel_layout       != audio.src.channel_layout ||
        af->frame->sample_rate   != audio.src.freq           ||
        (wanted_nb_samples       != af->frame->nb_samples && !audio.swr_ctx))
    {
        swr_free(&audio.swr_ctx);
        audio.swr_ctx = swr_alloc_set_opts(NULL, audio.tgt.channel_layout, audio.tgt.fmt, audio.tgt.freq, dec_channel_layout, (AVSampleFormat)af->frame->format, af->frame->sample_rate, 0, NULL);
        if (!audio.swr_ctx || swr_init(audio.swr_ctx) < 0)
        {
            av_log(NULL, AV_LOG_ERROR,
                   "Cannot create sample rate converter for conversion of %d Hz %s %d channels to %d Hz %s %d channels!\n",
                   af->frame->sample_rate, av_get_sample_fmt_name((AVSampleFormat)af->frame->format), af->frame->channels,
                   audio.tgt.freq, av_get_sample_fmt_name(audio.tgt.fmt), audio.tgt.channels);
            swr_free(&audio.swr_ctx);
            return -1;
        }
        audio.src.channel_layout = dec_channel_layout;
        audio.src.channels       = af->frame->channels;
        audio.src.freq = af->frame->sample_rate;
        audio.src.fmt = (AVSampleFormat)af->frame->format;
    }

    if (audio.swr_ctx)
    {
        const uint8_t **in = (const uint8_t **)af->frame->extended_data;
        uint8_t **out = &audio.buf1;
        int out_count = (int64_t)wanted_nb_samples * audio.tgt.freq / af->frame->sample_rate + 256;
        int out_size  = av_samples_get_buffer_size(NULL, audio.tgt.channels, out_count, audio.tgt.fmt, 0);
        int len2;
        if (out_size < 0)
        {
            av_log(NULL, AV_LOG_ERROR, "av_samples_get_buffer_size() failed\n");
            return -1;
        }
        if (wanted_nb_samples != af->frame->nb_samples) {
            if (swr_set_compensation(audio.swr_ctx, (wanted_nb_samples - af->frame->nb_samples) * audio.tgt.freq / af->frame->sample_rate,
                                     wanted_nb_samples * audio.tgt.freq / af->frame->sample_rate) < 0) {
                av_log(NULL, AV_LOG_ERROR, "swr_set_compensation() failed\n");
                return -1;
            }
        }
        av_fast_malloc(&audio.buf1, &audio.buf1_size, out_size);
        if (!audio.buf1)
            return AVERROR(ENOMEM);
        len2 = swr_convert(audio.swr_ctx, out, out_count, in, af->frame->nb_samples);
        if (len2 < 0) {
            av_log(NULL, AV_LOG_ERROR, "swr_convert() failed\n");
            return -1;
        }
        if (len2 == out_count) {
            av_log(NULL, AV_LOG_WARNING, "audio buffer is probably too small\n");
            if (swr_init(audio.swr_ctx) < 0)
                swr_free(&audio.swr_ctx);
        }
        audio.buf = audio.buf1;
        resampled_data_size = len2 * audio.tgt.channels * av_get_bytes_per_sample(audio.tgt.fmt);
    } else {
        audio.buf = af->frame->data[0];
        resampled_data_size = data_size;
    }

    audio_clock0 = audio_clock;
    /* update the audio clock with the pts */
    if (!isnan(af->pts))
        audio_clock = af->pts + (double) af->frame->nb_samples / af->frame->sample_rate;
    else
        audio_clock = NAN;
    audio_clock_serial = af->serial;
#ifdef DEBUG
    {
        static double last_clock;
        printf("audio: delay=%0.3f clock=%0.3f clock0=%0.3f\n",
               is->audio_clock - last_clock,
               is->audio_clock, audio_clock0);
        last_clock = is->audio_clock;
    }
#endif
    return resampled_data_size;
}

/* return the wanted number of samples to get better sync if sync_type is video
 * or external master clock */
int HVideoState::synchronize_audio(int nb_samples)
{
    int wanted_nb_samples = nb_samples;

    /* if not master, then we try to remove or add samples to correct the clock */
    if (get_master_sync_type() != SYNC_AUDIO_MASTER)
    {
        double diff, avg_diff;
        int min_nb_samples, max_nb_samples;

        diff = audclk.get_clock() - get_master_clock();

        if (!isnan(diff) && fabs(diff) < AV_SYNC_THRESHOLD_NO) {
            audio.diff_cum = diff + audio.diff_avg_coef * audio.diff_cum;
            if (audio.diff_avg_count < AUDIO_DIFF_AVG_NB) {
                /* not enough measures to have a correct estimate */
                audio.diff_avg_count++;
            } else {
                /* estimate the A-V difference */
                avg_diff = audio.diff_cum * (1.0 - audio.diff_avg_coef);

                if (fabs(avg_diff) >= audio.diff_threshold) {
                    wanted_nb_samples = nb_samples + (int)(diff * audio.src.freq);
                    min_nb_samples = ((nb_samples * (100 - SAMPLE_CORRECTION_PERCENT_MAX) / 100));
                    max_nb_samples = ((nb_samples * (100 + SAMPLE_CORRECTION_PERCENT_MAX) / 100));
                    wanted_nb_samples = av_clip(wanted_nb_samples, min_nb_samples, max_nb_samples);
                }
                av_log(NULL, AV_LOG_TRACE, "diff=%f adiff=%f sample_diff=%d apts=%0.3f %f\n",
                       diff, avg_diff, wanted_nb_samples - nb_samples,
                       audio_clock, audio.diff_threshold);
            }
        } else {
            /* too big difference : may be initial PTS errors, so
               reset A-V filter */
            audio.diff_avg_count = 0;
            audio.diff_cum       = 0;
        }
    }

    return wanted_nb_samples;
}

/* copy samples for viewing in editor window */
void HVideoState::update_sample_display(short *samples, int samples_size)
{
    int size, len;

    size = samples_size / sizeof(short);
    while (size > 0) {
        len = SAMPLE_ARRAY_SIZE - sample_array_index;
        if (len > size)
            len = size;
        memcpy(sample_array + sample_array_index, samples, len * sizeof(short));
        samples += len;
        sample_array_index += len;
        if (sample_array_index >= SAMPLE_ARRAY_SIZE)
            sample_array_index = 0;
        size -= len;
    }
}

int HVideoState::get_video_frame(AVFrame *frame)
{
    int got_picture;

    if ((got_picture = video.decoder.decode(frame, NULL)) < 0)
        return -1;

    if (got_picture) {
        double dpts = NAN;

        if (frame->pts != AV_NOPTS_VALUE)
            dpts = av_q2d(video.stream->time_base) * frame->pts;

        frame->sample_aspect_ratio = av_guess_sample_aspect_ratio(ic, video.stream, frame);

        if (framedrop>0 || (framedrop && get_master_sync_type() != SYNC_VIDEO_MASTER)) {
            if (frame->pts != AV_NOPTS_VALUE) {
                double diff = dpts - get_master_clock();
                if (!isnan(diff) && fabs(diff) < AV_SYNC_THRESHOLD_NO &&
                    diff - frame_last_filter_delay < 0 &&
                    video.decoder.pkt_serial == vidclk.serial &&
                    video.packets.nb_packets) {
                    frame_drops_early++;
                    av_frame_unref(frame);
                    got_picture = 0;
                }
            }
        }
    }

    return got_picture;
}

int HVideoState::queue_picture(AVFrame *src_frame, double pts, double duration, int64_t pos, int serial)
{
    HFrame *vp;

#if defined(DEBUG_SYNC)
    printf("frame_type=%c pts=%0.3f\n",
           av_get_picture_type_char(src_frame->pict_type), pts);
#endif

    if (!(vp = video.frames.peek_writeable()))
        return -1;

    vp->sar = src_frame->sample_aspect_ratio;
    vp->uploaded = 0;

    vp->width = src_frame->width;
    vp->height = src_frame->height;
    vp->format = src_frame->format;

    vp->pts = pts;
    vp->duration = duration;
    vp->pos = pos;
    vp->serial = serial;

    set_default_window_size(vp->width, vp->height, vp->sar);

    av_frame_move_ref(vp->frame, src_frame);
    video.frames.push();
    return 0;
}

int HVideoState::video_open()
{
    int w,h;

    w = screen_width ? screen_width : default_width;
    h = screen_height ? screen_height : default_height;

    if (!window_title)
        window_title = input_filename;
    SDL_SetWindowTitle(window, window_title);

    SDL_SetWindowSize(window, w, h);
    SDL_SetWindowPosition(window, screen_left, screen_top);
    if (is_full_screen)
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_ShowWindow(window);

    width  = w;
    height = h;
    return 0;
}

void HVideoState::video_refresh(double *remaining_time)
{
    double time;
    HFrame *sp, *sp2;

    if (!paused && get_master_sync_type() == SYNC_EXTERNAL_CLOCK && realtime)
        check_external_clock_speed();

    if (!display_disable && show_mode != SHOW_MODE_VIDEO && audio.stream)
    {
        time = av_gettime_relative() / 1000000.0;
        if (force_refresh || last_vis_time + rdftspeed < time)
        {
            video_display();
            last_vis_time = time;
        }
        *remaining_time = FFMIN(*remaining_time, last_vis_time + rdftspeed - time);
    }

    if (video.stream)
    {
    retry:
        if (video.frames.remaining() == 0)
        {
            // nothing to do, no picture to display in the queue
        } else {
            double last_duration, duration, delay;
            HFrame *vp, *lastvp;

            /* dequeue the picture */
            lastvp = video.frames.peek_last();
            vp = video.frames.peek();

            if (vp->serial != video.packets.serial)
            {
                video.frames.next();
                goto retry;
            }

            if (lastvp->serial != vp->serial)
                frame_timer = av_gettime_relative() / 1000000.0;

            if (paused)
                goto display;

            /* compute nominal last_duration */
            last_duration = vp_duration(lastvp, vp);
            delay = compute_target_delay(last_duration);

            time= av_gettime_relative()/1000000.0;
            if (time < frame_timer + delay) {
                *remaining_time = FFMIN(frame_timer + delay - time, *remaining_time);
                goto display;
            }

            frame_timer += delay;
            if (delay > 0 && time - frame_timer > AV_SYNC_THRESHOLD_MAX)
                frame_timer = time;

            SDL_LockMutex(video.frames.mutex);
            if (!isnan(vp->pts))
                update_video_pts(vp->pts, vp->pos, vp->serial);
            SDL_UnlockMutex(video.frames.mutex);

            if (video.frames.remaining() > 1)
            {
                HFrame *nextvp = video.frames.peek_next();
                duration = vp_duration(vp, nextvp);
                if(!step && (framedrop>0 || (framedrop && get_master_sync_type() != SYNC_VIDEO_MASTER)) && time > frame_timer + duration)
                {
                    frame_drops_late++;
                    video.frames.next();
                    goto retry;
                }
            }

            if (subtitle.stream)
            {
                while (subtitle.frames.remaining() > 0)
                {
                    sp = subtitle.frames.peek();

                    if (subtitle.frames.remaining() > 1)
                        sp2 = subtitle.frames.peek_next();
                    else
                        sp2 = NULL;

                    if (sp->serial != subtitle.packets.serial
                        || (vidclk.pts > (sp->pts + ((float) sp->sub.end_display_time / 1000)))
                        || (sp2 && vidclk.pts > (sp2->pts + ((float) sp2->sub.start_display_time / 1000))))
                    {
                        if (sp->uploaded) {
                            int i;
                            for (i = 0; i < sp->sub.num_rects; i++) {
                                AVSubtitleRect *sub_rect = sp->sub.rects[i];
                                uint8_t *pixels;
                                int pitch, j;

                                if (!SDL_LockTexture(sub_texture, (SDL_Rect *)sub_rect, (void **)&pixels, &pitch)) {
                                    for (j = 0; j < sub_rect->h; j++, pixels += pitch)
                                        memset(pixels, 0, sub_rect->w << 2);
                                    SDL_UnlockTexture(sub_texture);
                                }
                            }
                        }
                        subtitle.frames.next();
                    } else {
                        break;
                    }
                }
            }

            video.frames.next();
            force_refresh = 1;

            if (step && !paused)
                toggle_pause();
        }
    display:
        /* display picture */
        if (!display_disable && force_refresh && show_mode == SHOW_MODE_VIDEO && video.frames.rindex_shown)
            video_display();
    }
    force_refresh = 0;
    if (show_status) {
        AVBPrint buf;
        static int64_t last_time;
        int64_t cur_time;
        int aqsize, vqsize, sqsize;
        double av_diff;

        cur_time = av_gettime_relative();
        if (!last_time || (cur_time - last_time) >= 30000) {
            aqsize = 0;
            vqsize = 0;
            sqsize = 0;
            if (audio.stream)
                aqsize = audio.packets.size;
            if (video.stream)
                vqsize = video.packets.size;
            if (subtitle.stream)
                sqsize = subtitle.packets.size;
            av_diff = 0;
            if (audio.stream && video.stream)
                av_diff = audclk.get_clock() - vidclk.get_clock();
            else if (video.stream)
                av_diff = get_master_clock() - vidclk.get_clock();
            else if (audio.stream)
                av_diff = get_master_clock() - audclk.get_clock();

            av_bprint_init(&buf, 0, AV_BPRINT_SIZE_AUTOMATIC);
            av_bprintf(&buf,
                       "%7.2f %s:%7.3f fd=%4d aq=%5dKB vq=%5dKB sq=%5dB f=%ld/%ld\r",
                       get_master_clock(),
                       (audio.stream && video.stream) ? "A-V" : (video.stream ? "M-V" : (audio.stream ? "M-A" : "   ")),
                       av_diff,
                       frame_drops_early + frame_drops_late,
                       aqsize / 1024,
                       vqsize / 1024,
                       sqsize,
                       video.stream ? video.decoder.avctx->pts_correction_num_faulty_dts : 0,
                       video.stream ? video.decoder.avctx->pts_correction_num_faulty_pts : 0);

            if (show_status == 1 && AV_LOG_INFO > av_log_get_level())
                fprintf(stderr, "%s", buf.str);
            else
                av_log(NULL, AV_LOG_INFO, "%s", buf.str);

            fflush(stderr);
            av_bprint_finalize(&buf, NULL);

            last_time = cur_time;
        }
    }
}

void HVideoState::video_display()
{
    if (!width)
        video_open();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    if (audio.stream && show_mode != SHOW_MODE_VIDEO)
        video_audio_display();
    else if (video.stream)
        video_image_display();
    SDL_RenderPresent(renderer);
}

void HVideoState::video_audio_display()
{
    HVideoState *s = this;
    int i, i_start, x, y1, y, ys, delay, n, nb_display_channels;
    int ch, channels, h, h2;
    int64_t time_diff;
    int rdft_bits, nb_freq;

    for (rdft_bits = 1; (1 << rdft_bits) < 2 * s->height; rdft_bits++)
        ;
    nb_freq = 1 << (rdft_bits - 1);

    /* compute display index : center on currently output samples */
    channels = s->audio.tgt.channels;
    nb_display_channels = channels;
    if (!s->paused) {
        int data_used= s->show_mode == SHOW_MODE_WAVES ? s->width : (2*nb_freq);
        n = 2 * channels;
        delay = s->audio_write_buf_size;
        delay /= n;

        /* to be more precise, we take into account the time spent since
           the last buffer computation */
        if (audio_callback_time) {
            time_diff = av_gettime_relative() - audio_callback_time;
            delay -= (time_diff * s->audio.tgt.freq) / 1000000;
        }

        delay += 2 * data_used;
        if (delay < data_used)
            delay = data_used;

        i_start= x = compute_mod(s->sample_array_index - delay * channels, SAMPLE_ARRAY_SIZE);
        if (s->show_mode == SHOW_MODE_WAVES) {
            h = INT_MIN;
            for (i = 0; i < 1000; i += channels) {
                int idx = (SAMPLE_ARRAY_SIZE + x - i) % SAMPLE_ARRAY_SIZE;
                int a = s->sample_array[idx];
                int b = s->sample_array[(idx + 4 * channels) % SAMPLE_ARRAY_SIZE];
                int c = s->sample_array[(idx + 5 * channels) % SAMPLE_ARRAY_SIZE];
                int d = s->sample_array[(idx + 9 * channels) % SAMPLE_ARRAY_SIZE];
                int score = a - d;
                if (h < score && (b ^ c) < 0) {
                    h = score;
                    i_start = idx;
                }
            }
        }

        s->last_i_start = i_start;
    } else {
        i_start = s->last_i_start;
    }

    if (s->show_mode == SHOW_MODE_WAVES) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        /* total height for one channel */
        h = s->height / nb_display_channels;
        /* graph height / 2 */
        h2 = (h * 9) / 20;
        for (ch = 0; ch < nb_display_channels; ch++) {
            i = i_start + ch;
            y1 = s->ytop + ch * h + (h / 2); /* position of center line */
            for (x = 0; x < s->width; x++) {
                y = (s->sample_array[i] * h2) >> 15;
                if (y < 0) {
                    y = -y;
                    ys = y1 - y;
                } else {
                    ys = y1;
                }
                fill_rectangle(s->xleft + x, ys, 1, y);
                i += channels;
                if (i >= SAMPLE_ARRAY_SIZE)
                    i -= SAMPLE_ARRAY_SIZE;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

        for (ch = 1; ch < nb_display_channels; ch++) {
            y = s->ytop + ch * h;
            fill_rectangle(s->xleft, y, s->width, 1);
        }
    } else {
        if (realloc_texture(&s->vis_texture, SDL_PIXELFORMAT_ARGB8888, s->width, s->height, SDL_BLENDMODE_NONE, 1) < 0)
            return;

        nb_display_channels= FFMIN(nb_display_channels, 2);
        if (rdft_bits != audio.rdft_bits) {
            av_rdft_end(audio.rdft);
            av_free(audio.rdft_data);
            audio.rdft = av_rdft_init(rdft_bits, DFT_R2C);
            audio.rdft_bits = rdft_bits;
            audio.rdft_data = (FFTSample *)av_malloc_array(nb_freq, 4 *sizeof(*audio.rdft_data));
        }
        if (!audio.rdft || !audio.rdft_data){
            av_log(NULL, AV_LOG_ERROR, "Failed to allocate buffers for RDFT, switching to waves display\n");
            s->show_mode = SHOW_MODE_WAVES;
        } else {
            FFTSample *data[2];
            SDL_Rect rect = {.x = s->xpos, .y = 0, .w = 1, .h = s->height};
            uint32_t *pixels;
            int pitch;
            for (ch = 0; ch < nb_display_channels; ch++) {
                data[ch] = audio.rdft_data + 2 * nb_freq * ch;
                i = i_start + ch;
                for (x = 0; x < 2 * nb_freq; x++) {
                    double w = (x-nb_freq) * (1.0 / nb_freq);
                    data[ch][x] = s->sample_array[i] * (1.0 - w * w);
                    i += channels;
                    if (i >= SAMPLE_ARRAY_SIZE)
                        i -= SAMPLE_ARRAY_SIZE;
                }
                av_rdft_calc(audio.rdft, data[ch]);
            }
            /* Least efficient way to do this, we should of course
             * directly access it but it is more than fast enough. */
            if (!SDL_LockTexture(s->vis_texture, &rect, (void **)&pixels, &pitch)) {
                pitch >>= 2;
                pixels += pitch * s->height;
                for (y = 0; y < s->height; y++) {
                    double w = 1 / sqrt(nb_freq);
                    int a = sqrt(w * sqrt(data[0][2 * y + 0] * data[0][2 * y + 0] + data[0][2 * y + 1] * data[0][2 * y + 1]));
                    int b = (nb_display_channels == 2 ) ? sqrt(w * hypot(data[1][2 * y + 0], data[1][2 * y + 1]))
                                                       : a;
                    a = FFMIN(a, 255);
                    b = FFMIN(b, 255);
                    pixels -= pitch;
                    *pixels = (a << 16) + (b << 8) + ((a+b) >> 1);
                }
                SDL_UnlockTexture(s->vis_texture);
            }
            SDL_RenderCopy(renderer, s->vis_texture, NULL, NULL);
        }
        if (!s->paused)
            s->xpos++;
        if (s->xpos >= s->width)
            s->xpos= s->xleft;
    }
}

void HVideoState::video_image_display()
{
    HFrame *vp;
    HFrame *sp = NULL;
    SDL_Rect rect;

    vp = video.frames.peek_last();
    if (subtitle.stream)
    {
        if (subtitle.frames.remaining() > 0)
        {
            sp = subtitle.frames.peek();

            if (vp->pts >= sp->pts + ((float) sp->sub.start_display_time / 1000)) {
                if (!sp->uploaded) {
                    uint8_t* pixels[4];
                    int pitch[4];
                    int i;
                    if (!sp->width || !sp->height) {
                        sp->width = vp->width;
                        sp->height = vp->height;
                    }
                    if (realloc_texture(&sub_texture, SDL_PIXELFORMAT_ARGB8888, sp->width, sp->height, SDL_BLENDMODE_BLEND, 1) < 0)
                        return;

                    for (i = 0; i < sp->sub.num_rects; i++) {
                        AVSubtitleRect *sub_rect = sp->sub.rects[i];

                        sub_rect->x = av_clip(sub_rect->x, 0, sp->width );
                        sub_rect->y = av_clip(sub_rect->y, 0, sp->height);
                        sub_rect->w = av_clip(sub_rect->w, 0, sp->width  - sub_rect->x);
                        sub_rect->h = av_clip(sub_rect->h, 0, sp->height - sub_rect->y);

                        sub_convert_ctx = sws_getCachedContext(sub_convert_ctx,
                                                               sub_rect->w, sub_rect->h, AV_PIX_FMT_PAL8,
                                                               sub_rect->w, sub_rect->h, AV_PIX_FMT_BGRA,
                                                               0, NULL, NULL, NULL);
                        if (!sub_convert_ctx) {
                            av_log(NULL, AV_LOG_FATAL, "Cannot initialize the conversion context\n");
                            return;
                        }
                        if (!SDL_LockTexture(sub_texture, (SDL_Rect *)sub_rect, (void **)pixels, pitch)) {
                            sws_scale(sub_convert_ctx, (const uint8_t * const *)sub_rect->data, sub_rect->linesize,
                                      0, sub_rect->h, pixels, pitch);
                            SDL_UnlockTexture(sub_texture);
                        }
                    }
                    sp->uploaded = 1;
                }
            } else
                sp = NULL;
        }
    }

    calc_display_rect(&rect, xleft, ytop, width, height, vp->width, vp->height, vp->sar);

    if (!vp->uploaded) {
        if (upload_texture(&vid_texture, vp->frame, &img_convert_ctx) < 0)
            return;
        vp->uploaded = 1;
        vp->flip_v = vp->frame->linesize[0] < 0;
    }

    set_sdl_yuv_conversion_mode(vp->frame);
    SDL_RenderCopyEx(renderer, vid_texture, NULL, &rect, 0, NULL, vp->flip_v ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);
    set_sdl_yuv_conversion_mode(NULL);
    if (sp) {
#if USE_ONEPASS_SUBTITLE_RENDER
        SDL_RenderCopy(renderer, is->sub_texture, NULL, &rect);
#else
        int i;
        double xratio = (double)rect.w / (double)sp->width;
        double yratio = (double)rect.h / (double)sp->height;
        for (i = 0; i < sp->sub.num_rects; i++) {
            SDL_Rect *sub_rect = (SDL_Rect*)sp->sub.rects[i];
            SDL_Rect target;
            target.x = rect.x + sub_rect->x * xratio;
            target.y = rect.y + sub_rect->y * yratio;
            target.w = sub_rect->w * xratio;
            target.h = sub_rect->h * yratio;
            SDL_RenderCopy(renderer, sub_texture, sub_rect, &target);
        }
#endif
    }
}

void HVideoState::update_video_pts(double pts, int64_t pos, int serial)
{
    /* update current video pts */
    vidclk.set_clock( pts, serial);
    extclk.sync_clock(&vidclk);
}

#if CONFIG_AVFILTER

int HVideoState::configure_video_filters(AVFilterGraph *graph, const char *vfilters, AVFrame *frame)
{
    enum AVPixelFormat pix_fmts[FF_ARRAY_ELEMS(sdl_texture_format_map)];
    char sws_flags_str[512] = "";
    char buffersrc_args[256];
    int ret;
    AVFilterContext *filt_src = NULL, *filt_out = NULL, *last_filter = NULL;
    AVCodecParameters *codecpar = video.stream->codecpar;
    AVRational fr = av_guess_frame_rate(ic, video.stream, NULL);
    AVDictionaryEntry *e = NULL;
    int nb_pix_fmts = 0;
    int i, j;

    for (i = 0; i < renderer_info.num_texture_formats; i++) {
        for (j = 0; j < FF_ARRAY_ELEMS(sdl_texture_format_map) - 1; j++) {
            if (renderer_info.texture_formats[i] == sdl_texture_format_map[j].texture_fmt) {
                pix_fmts[nb_pix_fmts++] = sdl_texture_format_map[j].format;
                break;
            }
        }
    }
    pix_fmts[nb_pix_fmts] = AV_PIX_FMT_NONE;

    while ((e = av_dict_get(sws_dict, "", e, AV_DICT_IGNORE_SUFFIX))) {
        if (!strcmp(e->key, "sws_flags")) {
            av_strlcatf(sws_flags_str, sizeof(sws_flags_str), "%s=%s:", "flags", e->value);
        } else
            av_strlcatf(sws_flags_str, sizeof(sws_flags_str), "%s=%s:", e->key, e->value);
    }
    if (strlen(sws_flags_str))
        sws_flags_str[strlen(sws_flags_str)-1] = '\0';

    graph->scale_sws_opts = av_strdup(sws_flags_str);

    snprintf(buffersrc_args, sizeof(buffersrc_args),
             "video_size=%dx%d:pix_fmt=%d:time_base=%d/%d:pixel_aspect=%d/%d",
             frame->width, frame->height, frame->format,
             video.stream->time_base.num, video.stream->time_base.den,
             codecpar->sample_aspect_ratio.num, FFMAX(codecpar->sample_aspect_ratio.den, 1));
    if (fr.num && fr.den)
        av_strlcatf(buffersrc_args, sizeof(buffersrc_args), ":frame_rate=%d/%d", fr.num, fr.den);

    if ((ret = avfilter_graph_create_filter(&filt_src,
                                            avfilter_get_by_name("buffer"),
                                            "ffplay_buffer", buffersrc_args, NULL,
                                            graph)) < 0)
        goto fail;

    ret = avfilter_graph_create_filter(&filt_out,
                                       avfilter_get_by_name("buffersink"),
                                       "ffplay_buffersink", NULL, NULL, graph);
    if (ret < 0)
        goto fail;

    if ((ret = av_opt_set_int_list(filt_out, "pix_fmts", pix_fmts,  AV_PIX_FMT_NONE, AV_OPT_SEARCH_CHILDREN)) < 0)
        goto fail;

    last_filter = filt_out;

/* Note: this macro adds a filter before the lastly added filter, so the
 * processing order of the filters is in reverse */
#define INSERT_FILT(name, arg) do {                                          \
    AVFilterContext *filt_ctx;                                               \
                                                                             \
    ret = avfilter_graph_create_filter(&filt_ctx,                            \
                                       avfilter_get_by_name(name),           \
                                       "ffplay_" name, arg, NULL, graph);    \
    if (ret < 0)                                                             \
        goto fail;                                                           \
                                                                             \
    ret = avfilter_link(filt_ctx, 0, last_filter, 0);                        \
    if (ret < 0)                                                             \
        goto fail;                                                           \
                                                                             \
    last_filter = filt_ctx;                                                  \
} while (0)

    if (autorotate) {
        double theta  = get_rotation(video.stream);

        if (fabs(theta - 90) < 1.0) {
            INSERT_FILT("transpose", "clock");
        } else if (fabs(theta - 180) < 1.0) {
            INSERT_FILT("hflip", NULL);
            INSERT_FILT("vflip", NULL);
        } else if (fabs(theta - 270) < 1.0) {
            INSERT_FILT("transpose", "cclock");
        } else if (fabs(theta) > 1.0) {
            char rotate_buf[64];
            snprintf(rotate_buf, sizeof(rotate_buf), "%f*PI/180", theta);
            INSERT_FILT("rotate", rotate_buf);
        }
    }

    if ((ret = configure_filtergraph(graph, vfilters, filt_src, last_filter)) < 0)
        goto fail;

    in_video_filter  = filt_src;
    out_video_filter = filt_out;

fail:
    return ret;
}

#endif  /* CONFIG_AVFILTER */

/* seek in the stream */
void HVideoState::seek(int64_t pos, int64_t rel, int seek_by_bytes)
{
    if (seek_req)
        return;

    seek_pos = pos;
    seek_rel = rel;
    seek_flags &= ~AVSEEK_FLAG_BYTE;
    if (seek_by_bytes)
        seek_flags |= AVSEEK_FLAG_BYTE;
    seek_req = 1;
    SDL_CondSignal(continue_read_thread);
}

void HVideoState::seek_chapter(int incr)
{
    int64_t pos = get_master_clock() * AV_TIME_BASE;
    int i;

    if (!ic->nb_chapters)
        return;

    /* find the current chapter */
    for (i = 0; i < ic->nb_chapters; i++) {
        AVChapter *ch = ic->chapters[i];
        if (av_compare_ts(pos, AV_TIME_BASE_Q, ch->start, ch->time_base) < 0) {
            i--;
            break;
        }
    }

    i += incr;
    i = FFMAX(i, 0);
    if (i >= ic->nb_chapters)
        return;

    av_log(NULL, AV_LOG_VERBOSE, "Seeking to chapter %d.\n", i);
    seek(av_rescale_q(ic->chapters[i]->start, ic->chapters[i]->time_base, AV_TIME_BASE_Q), 0, 0);
}

void HVideoState::step_to_next_frame()
{
    /* if the stream is paused unpause it, then step */
    if (paused)
        toggle_pause();
    step = 1;
}

/* pause or resume the video */
void HVideoState::toggle_pause()
{
    if (paused)
    {
        frame_timer += av_gettime_relative() / 1000000.0 - vidclk.last_updated;
        if (read_pause_return != AVERROR(ENOSYS))
        {
            vidclk.paused = 0;
        }
        vidclk.set_clock(vidclk.get_clock(), vidclk.serial);
    }
    extclk.set_clock(extclk.get_clock(), extclk.serial);
    paused = audclk.paused = vidclk.paused = extclk.paused = !paused;
}

void HVideoState::toggle_mute()
{
    muted = !muted;
}

void HVideoState::toggle_full_screen()
{
    is_full_screen = !is_full_screen;
    SDL_SetWindowFullscreen(window, is_full_screen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
}

void HVideoState::toggle_audio_display()
{
    int next = show_mode;
    do
    {
        next = (next + 1) % SHOW_MODE_NB;
    } while (next != show_mode && ((next == SHOW_MODE_VIDEO && !video.stream) || (next != SHOW_MODE_VIDEO && !audio.stream)));
    if (show_mode != next)
    {
        force_refresh = 1;
        show_mode = (ShowMode)next;
    }
}

void HVideoState::update_volume(int sign, double step)
{
    double volume_level = audio_volume ? (20 * log(audio_volume / (double)SDL_MIX_MAXVOLUME) / log(10)) : -1000.0;
    int new_volume = lrint(SDL_MIX_MAXVOLUME * pow(10.0, (volume_level + sign * step) / 20.0));
    audio_volume = av_clip(audio_volume == new_volume ? (audio_volume + sign) : new_volume, 0, SDL_MIX_MAXVOLUME);
}

void HVideoState::cycle_channel(int codec_type)
{
    int start_index, stream_index;
    int old_index;
    AVStream *st;
    AVProgram *p = NULL;
    int nb_streams = ic->nb_streams;

    if (codec_type == AVMEDIA_TYPE_VIDEO) {
        start_index = video.stream_last;
        old_index = video.stream_index;
    } else if (codec_type == AVMEDIA_TYPE_AUDIO) {
        start_index = audio.stream_last;
        old_index = audio.stream_index;
    } else {
        start_index = subtitle.stream_last;
        old_index = subtitle.stream_index;
    }
    stream_index = start_index;

    if (codec_type != AVMEDIA_TYPE_VIDEO && video.stream_index != -1) {
        p = av_find_program_from_stream(ic, NULL, video.stream_index);
        if (p) {
            nb_streams = p->nb_stream_indexes;
            for (start_index = 0; start_index < nb_streams; start_index++)
                if (p->stream_index[start_index] == stream_index)
                    break;
            if (start_index == nb_streams)
                start_index = -1;
            stream_index = start_index;
        }
    }

    for (;;) {
        if (++stream_index >= nb_streams)
        {
            if (codec_type == AVMEDIA_TYPE_SUBTITLE)
            {
                stream_index = -1;
                subtitle.stream_last = -1;
                goto the_end;
            }
            if (start_index == -1)
                return;
            stream_index = 0;
        }
        if (stream_index == start_index)
            return;
        st = ic->streams[p ? p->stream_index[stream_index] : stream_index];
        if (st->codecpar->codec_type == codec_type) {
            /* check that parameters are OK */
            switch (codec_type) {
            case AVMEDIA_TYPE_AUDIO:
                if (st->codecpar->sample_rate != 0 &&
                    st->codecpar->channels != 0)
                    goto the_end;
                break;
            case AVMEDIA_TYPE_VIDEO:
            case AVMEDIA_TYPE_SUBTITLE:
                goto the_end;
            default:
                break;
            }
        }
    }
the_end:
    if (p && stream_index != -1)
        stream_index = p->stream_index[stream_index];
    av_log(NULL, AV_LOG_INFO, "Switch %s stream from #%d to #%d\n",
           av_get_media_type_string((AVMediaType)codec_type),
           old_index,
           stream_index);

    if (codec_type == AVMEDIA_TYPE_VIDEO)
    {
        video.close_stream(old_index);
        video.open_stream(stream_index, ic, video_codec_name);
    }
    else if (codec_type == AVMEDIA_TYPE_AUDIO)
    {
        audio.close_stream(old_index);
        audio.open_stream(stream_index, ic, audio_codec_name);
    }
    else
    {
        subtitle.close_stream(old_index);
        subtitle.open_stream(stream_index, ic, subtitle_codec_name);
    }
}

// 是否退出事件
bool is_exit_event(SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN)
        return exit_on_keydown || event->key.keysym.sym == SDLK_ESCAPE || event->key.keysym.sym == SDLK_q;
    if (event->type == SDL_MOUSEBUTTONDOWN)
        return exit_on_mousedown;
    if (event->type == SDL_QUIT || event->type == FF_QUIT_EVENT)
        return true;
    return false;
}
void refresh_loop_wait_event(HVideoState *is, SDL_Event *event)
{
    double remaining_time = 0.0;
    SDL_PumpEvents();
    while (!SDL_PeepEvents(event, 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_LASTEVENT)) {
        if (!cursor_hidden && av_gettime_relative() - cursor_last_shown > CURSOR_HIDE_DELAY) {
            SDL_ShowCursor(0);
            cursor_hidden = 1;
        }
        if (remaining_time > 0.0)
            av_usleep((int64_t)(remaining_time * 1000000.0));
        remaining_time = REFRESH_RATE;
        if (is->show_mode != SHOW_MODE_NONE && (!is->paused || is->force_refresh))
            is->video_refresh(&remaining_time);
        SDL_PumpEvents();
    }
}

void event_loop(HVideoState *cur_stream)
{
    SDL_Event event;
    double incr, pos, frac;

    for (;;) {
        double x;
        refresh_loop_wait_event(cur_stream, &event);
        if (is_exit_event(&event))
            break;
        switch (event.type)
        {
        case SDL_KEYDOWN:
            // If we don't yet have a window, skip all key events, because read_thread might still be initializing...
            if (!cur_stream->width)
                continue;
            switch (event.key.keysym.sym) {
            case SDLK_f:
                cur_stream->toggle_full_screen();
                cur_stream->force_refresh = 1;
                break;
            case SDLK_p:
            case SDLK_SPACE:
                cur_stream->toggle_pause();
                break;
            case SDLK_m:
                cur_stream->toggle_mute();
                break;
            case SDLK_KP_MULTIPLY:
            case SDLK_0:
                cur_stream->update_volume(1, SDL_VOLUME_STEP);
                break;
            case SDLK_KP_DIVIDE:
            case SDLK_9:
                cur_stream->update_volume(-1, SDL_VOLUME_STEP);
                break;
            case SDLK_s: // S: Step to next frame
                cur_stream->step_to_next_frame();
                break;
            case SDLK_a:
                cur_stream->cycle_channel(AVMEDIA_TYPE_AUDIO);
                break;
            case SDLK_v:
                cur_stream->cycle_channel(AVMEDIA_TYPE_VIDEO);
                break;
            case SDLK_c:
                cur_stream->cycle_channel(AVMEDIA_TYPE_VIDEO);
                cur_stream->cycle_channel(AVMEDIA_TYPE_AUDIO);
                cur_stream->cycle_channel(AVMEDIA_TYPE_SUBTITLE);
                break;
            case SDLK_t:
                cur_stream->cycle_channel(AVMEDIA_TYPE_SUBTITLE);
                break;
            case SDLK_w:
#if CONFIG_AVFILTER
                if (cur_stream->show_mode == SHOW_MODE_VIDEO && cur_stream->vfilter_idx < nb_vfilters - 1) {
                    if (++cur_stream->vfilter_idx >= nb_vfilters)
                        cur_stream->vfilter_idx = 0;
                } else {
                    cur_stream->vfilter_idx = 0;
                    cur_stream->toggle_audio_display();
                }
#else
                cur_stream->toggle_audio_display();
#endif
                break;
            case SDLK_PAGEUP:
                if (cur_stream->ic->nb_chapters <= 1) {
                    incr = 600.0;
                    goto do_seek;
                }
                cur_stream->seek_chapter(1);
                break;
            case SDLK_PAGEDOWN:
                if (cur_stream->ic->nb_chapters <= 1) {
                    incr = -600.0;
                    goto do_seek;
                }
                cur_stream->seek_chapter(-1);
                break;
            case SDLK_LEFT:
                incr = seek_interval ? -seek_interval : -10.0;
                goto do_seek;
            case SDLK_RIGHT:
                incr = seek_interval ? seek_interval : 10.0;
                goto do_seek;
            case SDLK_UP:
                incr = 60.0;
                goto do_seek;
            case SDLK_DOWN:
                incr = -60.0;
            do_seek:
                if (seek_by_bytes) {
                    pos = -1;
                    if (pos < 0 && cur_stream->video.stream_index >= 0)
                        pos = cur_stream->video.frames.last_pos();
                    if (pos < 0 && cur_stream->audio.stream_index >= 0)
                        pos = cur_stream->audio.frames.last_pos();
                    if (pos < 0)
                        pos = avio_tell(cur_stream->ic->pb);
                    if (cur_stream->ic->bit_rate)
                        incr *= cur_stream->ic->bit_rate / 8.0;
                    else
                        incr *= 180000.0;
                    pos += incr;
                    cur_stream->seek(pos, incr, 1);
                } else {
                    pos = cur_stream->get_master_clock();
                    if (isnan(pos))
                        pos = (double)cur_stream->seek_pos / AV_TIME_BASE;
                    pos += incr;
                    if (cur_stream->ic->start_time != AV_NOPTS_VALUE && pos < cur_stream->ic->start_time / (double)AV_TIME_BASE)
                        pos = cur_stream->ic->start_time / (double)AV_TIME_BASE;
                    cur_stream->seek((int64_t)(pos * AV_TIME_BASE), (int64_t)(incr * AV_TIME_BASE), 0);
                }
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                static int64_t last_mouse_left_click = 0;
                if (av_gettime_relative() - last_mouse_left_click <= 500000) {
                    cur_stream->toggle_full_screen();
                    cur_stream->force_refresh = 1;
                    last_mouse_left_click = 0;
                } else {
                    last_mouse_left_click = av_gettime_relative();
                }
            }
        case SDL_MOUSEMOTION:
            if (cursor_hidden) {
                SDL_ShowCursor(1);
                cursor_hidden = 0;
            }
            cursor_last_shown = av_gettime_relative();
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button != SDL_BUTTON_RIGHT)
                    break;
                x = event.button.x;
            } else {
                if (!(event.motion.state & SDL_BUTTON_RMASK))
                    break;
                x = event.motion.x;
            }
            if (seek_by_bytes || cur_stream->ic->duration <= 0) {
                uint64_t size =  avio_size(cur_stream->ic->pb);
                cur_stream->seek(size*x/cur_stream->width, 0, 1);
            } else {
                int64_t ts;
                int ns, hh, mm, ss;
                int tns, thh, tmm, tss;
                tns  = cur_stream->ic->duration / 1000000LL;
                thh  = tns / 3600;
                tmm  = (tns % 3600) / 60;
                tss  = (tns % 60);
                frac = x / cur_stream->width;
                ns   = frac * tns;
                hh   = ns / 3600;
                mm   = (ns % 3600) / 60;
                ss   = (ns % 60);
                av_log(NULL, AV_LOG_INFO,
                       "Seek to %2.0f%% (%2d:%02d:%02d) of total duration (%2d:%02d:%02d)       \n", frac*100,
                       hh, mm, ss, thh, tmm, tss);
                ts = frac * cur_stream->ic->duration;
                if (cur_stream->ic->start_time != AV_NOPTS_VALUE)
                    ts += cur_stream->ic->start_time;
                cur_stream->seek(ts, 0, 0);
            }
            break;
        case SDL_WINDOWEVENT:
            switch (event.window.event) {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                screen_width  = cur_stream->width  = event.window.data1;
                screen_height = cur_stream->height = event.window.data2;
                if (cur_stream->vis_texture) {
                    SDL_DestroyTexture(cur_stream->vis_texture);
                    cur_stream->vis_texture = NULL;
                }
            case SDL_WINDOWEVENT_EXPOSED:
                cur_stream->force_refresh = 1;
            }
            break;
        default:
            break;
        }
    }
}

HFFPlayerControl::HFFPlayerControl(QObject *parent) :
    QThread(parent),
    d_ptr(new HFFPlayerControlPrivate)
{
    avdevice_register_all();
    avformat_network_init();
    av_log_set_flags(AV_LOG_SKIP_REPEATED);
}

HFFPlayerControl::~HFFPlayerControl()
{
    avformat_network_deinit();
}

void HFFPlayerControl::setUrl(const QString &value)
{
    d_ptr->url = value;
}

void HFFPlayerControl::play()
{
    start();
}

void HFFPlayerControl::run()
{
    auto str = d_ptr->url.toStdString();
    input_filename = str.c_str();
    if (!input_filename)
    {
        av_log(nullptr, AV_LOG_FATAL, "An input file must be specified\n");
        return;
    }
    if (display_disable)
        video_disable = 1;

    if (!initSDL())
        return;

    av_init_packet(&flush_pkt);
    flush_pkt.data = (uint8_t *)&flush_pkt;

    if (!initVideoState())
        return;

    event_loop(d_ptr->is);
    free();
}

bool HFFPlayerControl::initSDL()
{
    int flags = SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER;
    if (audio_disable)
    {
        flags &= ~SDL_INIT_AUDIO;
    }
    else
    {
        /* Try to work around an occasional ALSA buffer underflow issue when the
         * period size is NPOT due to ALSA resampling by forcing the buffer size. */
        if (!SDL_getenv("SDL_AUDIO_ALSA_SET_BUFFER_SIZE"))
            SDL_setenv("SDL_AUDIO_ALSA_SET_BUFFER_SIZE", "1", 1);
    }
    if (display_disable)
        flags &= ~SDL_INIT_VIDEO;
    if (SDL_Init(flags))
    {
        av_log(nullptr, AV_LOG_FATAL, "Could not initialize SDL - %s\n", SDL_GetError());
        return false;
    }

    SDL_EventState(SDL_SYSWMEVENT, SDL_IGNORE);
    SDL_EventState(SDL_USEREVENT, SDL_IGNORE);

    if (!display_disable)
    {
        flags = SDL_WINDOW_OPENGL;
        if (alwaysontop)
            flags |= SDL_WINDOW_ALWAYS_ON_TOP;
        if (borderless)
            flags |= SDL_WINDOW_BORDERLESS;
        else
            flags |= SDL_WINDOW_RESIZABLE;
        window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, default_width, default_height, flags);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        if (window)
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (!renderer)
            {
                av_log(nullptr, AV_LOG_WARNING, "Failed to initialize a hardware accelerated renderer: %s\n", SDL_GetError());
                renderer = SDL_CreateRenderer(window, -1, 0);
            }
            if (renderer)
            {
                if (!SDL_GetRendererInfo(renderer, &renderer_info))
                    av_log(nullptr, AV_LOG_VERBOSE, "Initialized %s renderer.\n", renderer_info.name);
            }
        }
        if (!window || !renderer || !renderer_info.num_texture_formats)
        {
            av_log(nullptr, AV_LOG_FATAL, "Failed to create window or renderer: %s", SDL_GetError());
            free();
            return false;
        }
    }
    return true;
}

bool HFFPlayerControl::initVideoState()
{
    d_ptr->is = new HVideoState;
    if (!d_ptr->is->init(input_filename, file_iformat))
    {
        av_log(nullptr, AV_LOG_FATAL, "Failed to initialize media stream!\n");
        free();
        return false;
    }
    return true;
}

void HFFPlayerControl::free()
{
    if (d_ptr->is)
    {
        d_ptr->is->destroy();
        delete d_ptr->is;
    }
    av_packet_unref(&flush_pkt);
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    uninit_opts();
#if CONFIG_AVFILTER
    av_freep(&vfilters_list);
#endif
    if (show_status)
        printf("\n");
    SDL_Quit();
    av_log(nullptr, AV_LOG_QUIET, "%s", "");
}

HE_END_NAMESPACE

