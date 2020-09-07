#include "HFFStreamsControl_p.h"
#include "HFFCmdUtil.h"
#include "HFFSourceControl.h"
#include "HFFDataControl.h"
#include "HFFDecoderControl.h"
#include <QtCore/QRect>
#include <QtCore/QThread>

extern "C" {
#include "libavutil/bprint.h"
////#include "libavutil/display.h"
#ifdef CONFIG_AVFILTER
# include "libavfilter/buffersink.h"
# include "libavfilter/buffersrc.h"
#endif
}

using namespace std;

HE_CONTROL_BEGIN_NAMESPACE

#ifdef CONFIG_AVFILTER
bool configure_filter_graph(AVFilterGraph *graph, const QString &filters, AVFilterContext *source, AVFilterContext *sink)
{
    bool ret = false;
    AVFilterInOut *outputs = nullptr;
    AVFilterInOut *inputs = nullptr;
    auto nb_filters = graph->nb_filters;

    try
    {
        if (!filters.isEmpty())
        {
            outputs = avfilter_inout_alloc();
            inputs  = avfilter_inout_alloc();
            if (!outputs || !inputs)
                throw "";

            outputs->name       = av_strdup("in");
            outputs->filter_ctx = source;
            outputs->pad_idx    = 0;
            outputs->next       = nullptr;
            inputs->name        = av_strdup("out");
            inputs->filter_ctx  = sink;
            inputs->pad_idx     = 0;
            inputs->next        = nullptr;
            if (avfilter_graph_parse_ptr(graph, filters.toStdString().c_str(), &inputs, &outputs, nullptr) < 0)
                throw "";
        }
        else
        {
            if (avfilter_link(source, 0, sink, 0) < 0)
                throw "";
        }
        // Reorder the filters to ensure that inputs of the custom filters are merged first
        for (uint i = 0; i < graph->nb_filters - nb_filters; i++)
            FFSWAP(AVFilterContext*, graph->filters[i], graph->filters[i + nb_filters]);
        ret = avfilter_graph_config(graph, nullptr) >= 0;
    }
    catch (...)
    {
        ret = false;
    }
    avfilter_inout_free(&outputs);
    avfilter_inout_free(&inputs);
    return ret;
}
#endif

class HFFStreamsControlThread : public QThread
{
public:
    HFFStreamsControlThread(HFFStreamsControl *streams);

protected:
    void run() override;

private:
    HFFStreamsControl *_streams;
};

HFFStreamsControlThread::HFFStreamsControlThread(HFFStreamsControl *streams) :
    QThread(streams)
{
    _streams = streams;
}

void HFFStreamsControlThread::run()
{
    _streams->run();
}

HFFStreamsControl::HFFStreamsControl(HFFSourceControl *source) :
    QObject(source),
    d_ptr(new HFFStreamsControlPrivate)
{
    d_ptr->source = source;
    init();
}

HFFStreamsControl::HFFStreamsControl(HFFStreamsControlPrivate &p, HFFSourceControl *source) :
    QObject(source),
    d_ptr(&p)
{
    d_ptr->source = source;
    init();
}

HFFStreamsControl::~HFFStreamsControl()
{
    close();
}

bool HFFStreamsControl::is_open()
{
    return d_ptr->stream_index >= 0;
}

bool HFFStreamsControl::is_finish()
{
    if (d_ptr->stream_index < 0)
        return true;
    return d_ptr->decoder->finish_serial() == *d_ptr->packets->serial() && (frame_remaining() == 0);
}

int *HFFStreamsControl::packets_serial()
{
    return d_ptr->packets->serial();
}

int HFFStreamsControl::packets_size()
{
    return d_ptr->packets->size();
}

int HFFStreamsControl::frame_remaining()
{
    return d_ptr->frames->remaining();
}

int HFFStreamsControl::frame_rindex_shown()
{
    return d_ptr->frames->rindex_shown();
}

int HFFStreamsControl::speed_factor()
{
    if (d_ptr->stream_index < 0 || d_ptr->packets->remaining() > EXTERNAL_CLOCK_MAX_FRAMES)
        return 1;
    if (d_ptr->stream_index >= 0 && d_ptr->packets->remaining() <= EXTERNAL_CLOCK_MIN_FRAMES)
        return -1;
    return 0;
}

bool HFFStreamsControl::has_enough_packets()
{
    return d_ptr->stream_index < 0 ||
           (d_ptr->stream->disposition & AV_DISPOSITION_ATTACHED_PIC) ||
           d_ptr->packets->has_enough_packets(av_q2d(d_ptr->stream->time_base));
}

void HFFStreamsControl::init(int max_size, bool keep_last)
{
    d_ptr->frames->init(max_size, keep_last);
}

bool HFFStreamsControl::open(int index, AVFormatContext *ctx)
{
    if (index < 0 || index >= ctx->nb_streams)
        return false;

    if (d_ptr->fmt_ctx != ctx)
        d_ptr->fmt_ctx = ctx;
    d_ptr->stream_last = index;
    if (!open_codec_context(index))
        return false;

    if (!open_else())
        return false;

    d_ptr->fmt_ctx->streams[index]->discard = AVDISCARD_DEFAULT;
    d_ptr->stream_index = index;
    d_ptr->stream = ctx->streams[index];
    d_ptr->decoder->open(d_ptr->codec_ctx);
    if ((d_ptr->fmt_ctx->iformat->flags & (AVFMT_NOBINSEARCH | AVFMT_NOGENSEARCH | AVFMT_NO_BYTE_SEEK)) && !d_ptr->fmt_ctx->iformat->read_seek)
        d_ptr->decoder->set_start_pts(d_ptr->stream->start_time, d_ptr->stream->time_base);
    emit open_finished();
    return true;
}

void HFFStreamsControl::close()
{
    if (d_ptr->stream_index < 0)
        return;

    abort();
    close_else();
    d_ptr->decoder->close();
    d_ptr->fmt_ctx->streams[d_ptr->stream_index]->discard = AVDISCARD_ALL;
    d_ptr->stream = nullptr;
    d_ptr->stream_index = -1;
    if (d_ptr->codec_ctx)
        avcodec_free_context(&d_ptr->codec_ctx);
    emit close_finished();
}

void HFFStreamsControl::start()
{
    if (d_ptr->stream_index < 0)
        return;
    d_ptr->packets->start();
    d_ptr->frames->start();
    d_ptr->thread->start();
}

void HFFStreamsControl::abort()
{
    if (d_ptr->stream_index < 0)
        return;
    d_ptr->packets->abort();
    d_ptr->frames->abort();
    if (d_ptr->thread->isRunning())
        d_ptr->thread->wait();
    d_ptr->packets->flush();
    d_ptr->frames->flush();
}

bool HFFStreamsControl::packet_put(AVPacket *pkt)
{
    if (d_ptr->stream_index < 0 || pkt->stream_index != d_ptr->stream_index)
        return false;
    return d_ptr->packets->put(pkt);
}

void HFFStreamsControl::packet_put_flush()
{
    if (d_ptr->stream_index < 0)
        return;
    d_ptr->packets->flush();
    d_ptr->packets->put(&flush_pkt);
}

void HFFStreamsControl::packet_put_null()
{
    if (d_ptr->stream_index < 0)
        return;
    AVPacket pkt1, *pkt = &pkt1;
    av_init_packet(pkt);
    pkt->data = nullptr;
    pkt->size = 0;
    pkt->stream_index = d_ptr->stream_index;
    d_ptr->packets->put(pkt);
}

bool HFFStreamsControl::packet_put_attached()
{
    if (d_ptr->stream == nullptr || (d_ptr->stream->disposition & AV_DISPOSITION_ATTACHED_PIC) == 0)
        return true;

    AVPacket pkt;
    if (av_packet_ref(&pkt, &d_ptr->stream->attached_pic) < 0)
    {
        av_log(nullptr, AV_LOG_FATAL, "Could not copy attached packet.\n");
        return false;
    }
    d_ptr->packets->put(&pkt);
    packet_put_null();
    return true;
}

int64_t HFFStreamsControl::frame_last_pos()
{
    auto frame = frame_peek_last();
    if (d_ptr->frames->rindex_shown() && frame->serial == *d_ptr->packets->serial())
        return frame->pos;
    return -1;
}

HFFFrame *HFFStreamsControl::frame_peek_last()
{
    return d_ptr->frames->peek_last();
}

void HFFStreamsControl::frame_next()
{
    d_ptr->frames->next();
}

bool HFFStreamsControl::open_codec_context(int index)
{
    d_ptr->codec_ctx = avcodec_alloc_context3(nullptr);
    if (!d_ptr->codec_ctx)
        return false;
    if (avcodec_parameters_to_context(d_ptr->codec_ctx, d_ptr->fmt_ctx->streams[index]->codecpar) < 0)
    {
        av_log(nullptr, AV_LOG_FATAL, "Couldn't set parameters to codec context.\n");
        return false;
    }
    d_ptr->codec_ctx->pkt_timebase = d_ptr->fmt_ctx->streams[index]->time_base;

    auto codec = avcodec_find_decoder(d_ptr->codec_ctx->codec_id);
    if (!d_ptr->forced_codec_name.isEmpty())
        codec = avcodec_find_decoder_by_name(d_ptr->forced_codec_name.toStdString().data());
    if (!codec)
    {
        if (d_ptr->forced_codec_name.isEmpty())
            av_log(nullptr, AV_LOG_FATAL, "No codec could be found with name '%s'\n", d_ptr->forced_codec_name.toStdString().data());
        else
            av_log(nullptr, AV_LOG_FATAL, "No decoder could be found for codec %s\n", avcodec_get_name(d_ptr->codec_ctx->codec_id));
        return false;
    }
    d_ptr->codec_ctx->codec_id = codec->id;

    int stream_lowres = d_ptr->lowres;
    if (stream_lowres > codec->max_lowres)
    {
        av_log(d_ptr->codec_ctx, AV_LOG_WARNING, "The maximum value for lowres supported by the decoder is %d.\n", codec->max_lowres);
        stream_lowres = codec->max_lowres;
    }
    d_ptr->codec_ctx->lowres = stream_lowres;

    if (d_ptr->fast)
        d_ptr->codec_ctx->flags2 |= AV_CODEC_FLAG2_FAST;

    bool ret = true;
    auto opts = filter_codec_opts(codec_opts, d_ptr->codec_ctx->codec_id, d_ptr->fmt_ctx, d_ptr->fmt_ctx->streams[index], codec);
    try
    {
        if (!av_dict_get(opts, "threads", nullptr, 0))
            av_dict_set(&opts, "threads", "auto", 0);
        if (stream_lowres)
            av_dict_set_int(&opts, "lowres", stream_lowres, 0);
        if (d_ptr->codec_ctx->codec_type == AVMEDIA_TYPE_VIDEO || d_ptr->codec_ctx->codec_type == AVMEDIA_TYPE_AUDIO)
            av_dict_set(&opts, "refcounted_frames", "1", 0);

        if (avcodec_open2(d_ptr->codec_ctx, codec, &opts) < 0)
        {
            av_log(nullptr, AV_LOG_FATAL, "Couldn't open codec.\n");
            throw "";
        }
        if (auto t = av_dict_get(opts, "", nullptr, AV_DICT_IGNORE_SUFFIX))
        {
            av_log(nullptr, AV_LOG_ERROR, "Option %s not found.\n", t->key);
            throw "";
        }
    }
    catch (...)
    {
        ret = false;
    }
    av_dict_free(&opts);
    return ret;
}

void HFFStreamsControl::init()
{
    d_ptr->frames = new HFFFrameQueue(this);
    d_ptr->packets = new HFFPacketQueue(this);
    d_ptr->decoder = new HFFDecoderControl(this);
    d_ptr->thread = new HFFStreamsControlThread(this);
    connect(d_ptr->decoder, &HFFDecoderControl::empty_packet_queue, d_ptr->source, &HFFSourceControl::wake);
}

HFFVideoStreamsControl::HFFVideoStreamsControl(HFFSourceControl *source) :
    HFFStreamsControl(*new HFFVideoStreamsControlPrivate, source)
{
}

HFFVideoStreamsControl::~HFFVideoStreamsControl()
{
}

AVProgram *HFFVideoStreamsControl::find_program()
{
    Q_D(HFFVideoStreamsControl);
    if (d->stream_index < 0)
        return nullptr;
    return av_find_program_from_stream(d->fmt_ctx, nullptr, d->stream_index);
}

void HFFVideoStreamsControl::switch_channel(AVProgram */*p*/)
{
    Q_D(HFFVideoStreamsControl);
    auto start_index = d->stream_last;
    auto old_index = d->stream_index;
    auto stream_index = start_index;
    auto nb_streams = d->fmt_ctx->nb_streams;

    while (true)
    {
        if (++stream_index >= nb_streams)
        {
            if (start_index == -1)
                return;
            stream_index = 0;
        }
        if (stream_index == start_index)
            return;
        auto st = d->fmt_ctx->streams[stream_index];
        if (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO)
            break;
    }

    av_log(nullptr, AV_LOG_INFO, "Switch %s stream from #%d to #%d\n", av_get_media_type_string(AVMEDIA_TYPE_VIDEO), old_index, stream_index);
    close();
    open(stream_index, d->fmt_ctx);
}

bool HFFVideoStreamsControl::packet_put(AVPacket *pkt)
{
    if (d_ptr->stream_index < 0 || pkt->stream_index != d_ptr->stream_index || d_ptr->stream->disposition & AV_DISPOSITION_ATTACHED_PIC)
        return false;
    return d_ptr->packets->put(pkt);
}

void HFFVideoStreamsControl::set_pix_fmts(QList<int> value)
{
    Q_D(HFFVideoStreamsControl);
    for (int i = 0; i < value.size() && i < 100; i++)
        d->pix_fmts[i] = (AVPixelFormat)value.at(i);
}

void HFFVideoStreamsControl::add_frame_timer(double value)
{
    Q_D(HFFVideoStreamsControl);
    d->frame_timer += value;
}

int HFFVideoStreamsControl::frame_handle(bool paused, int step, double *remaining_time)
{
    Q_D(HFFVideoStreamsControl);

    auto frame = d->frames->peek();
    if (frame->serial != *packets_serial())
        return 0;

    auto last_frame = frame_peek_last();
    if (last_frame->serial != frame->serial)
        d->frame_timer = av_gettime_relative() / 1000000.0;

    if (paused)
        return -1;

    // compute nominal last_duration
    auto last_duration = compute_frame_duration(last_frame, frame);
    auto delay = compute_target_delay(last_duration);
    auto time = av_gettime_relative() / 1000000.0;
    if (time < d->frame_timer + delay)
    {
        *remaining_time = d->frame_timer + delay - time;
        return -1;
    }

    d->frame_timer += delay;
    if (delay > 0 && time - d->frame_timer > AV_SYNC_THRESHOLD_MAX)
        d->frame_timer = time;

    if (!isnan(frame->pts))
        d->source->update_video_pts(frame->pts, frame->pos, frame->serial);

    if (d->frames->remaining() > 1)
    {
        auto next_frame = d_ptr->frames->peek_next();
        auto duration = compute_frame_duration(frame, next_frame);
        if(!step && is_frame_drop() && time > d->frame_timer + duration)
        {
            d->frame_drops_late++;
            return 0;
        }
    }
    return 1;
}

bool HFFVideoStreamsControl::open_else()
{
    Q_D(HFFVideoStreamsControl);
    d->max_frame_duration = (d->fmt_ctx->iformat->flags & AVFMT_TS_DISCONT) ? 10.0 : 3600.0;
    d->frame_timer = 0.0;
    d->frame_last_filter_delay = 0.0;
    d->frame_drops_early = 0;
#ifdef CONFIG_AVFILTER
    d->filter_idx = 0;
#endif
    return true;
}

void HFFVideoStreamsControl::close_else()
{
    Q_D(HFFVideoStreamsControl);
#ifdef CONFIG_AVFILTER
    if (d->filter_graph)
        avfilter_graph_free(&d->filter_graph);
#endif
}

void HFFVideoStreamsControl::run()
{
    Q_D(HFFVideoStreamsControl);
    auto frame = av_frame_alloc();
    if (!frame)
        return;

    int ret = 0;
    int pkt_serial = -1;
    auto frame_rate = av_guess_frame_rate(d->fmt_ctx, d->stream, nullptr);
    auto time_base = d_ptr->stream->time_base;

#ifdef CONFIG_AVFILTER
    AVPixelFormat last_format = AV_PIX_FMT_NONE;
    int last_width = 0;
    int last_height = 0;
    int last_serial = -1;
    int last_filter_idx = 0;
#endif

    while (ret >= 0)
    {
        ret = decode(frame);
        if (ret < 0)
            break;
        if (ret == 0)
            continue;

         pkt_serial = d->decoder->pkt_serial();

#ifdef CONFIG_AVFILTER
        if (last_width != frame->width ||
            last_height != frame->height ||
            last_format != frame->format ||
            last_serial != pkt_serial ||
            last_filter_idx != d->filter_idx)
        {
            av_log(nullptr, AV_LOG_DEBUG,
                   "Video frame changed from size:%dx%d format:%s serial:%d to size:%dx%d format:%s serial:%d\n",
                   last_width, last_height,
                   (const char *)av_x_if_null(av_get_pix_fmt_name(last_format), "none"), last_serial,
                   frame->width, frame->height,
                   (const char *)av_x_if_null(av_get_pix_fmt_name((AVPixelFormat)frame->format), "none"), pkt_serial);

            auto filers = d->filter_idx < 0 || d->filter_idx >= d->filters.size() ? "" : d->filters.at(d->filter_idx);
            if (!configure_filters(filers, frame))
            {
                d->source->set_abort();
                break;
            }
            last_width = frame->width;
            last_height = frame->height;
            last_format = (AVPixelFormat)frame->format;
            last_serial = pkt_serial;
            last_filter_idx = d->filter_idx;
            frame_rate = av_buffersink_get_frame_rate(d->filter_out);
        }
        if (av_buffersrc_add_frame(d->filter_in, frame) < 0)
            break;

        while (ret >= 0)
        {
            d->frame_last_returned_time = av_gettime_relative() / 1000000.0;
            ret = av_buffersink_get_frame_flags(d->filter_out, frame, 0);
            if (ret < 0)
            {
                if (ret == AVERROR_EOF)
                    d->decoder->set_finish();
                ret = 0;
                break;
            }

            d->frame_last_filter_delay = av_gettime_relative() / 1000000.0 - d->frame_last_returned_time;
            if (fabs(d->frame_last_filter_delay) > AV_SYNC_THRESHOLD_NO / 10.0)
                d->frame_last_filter_delay = 0;
            time_base = av_buffersink_get_time_base(d->filter_out);
#endif
            auto duration = (frame_rate.num && frame_rate.den ? av_q2d((AVRational){frame_rate.den, frame_rate.num}) : 0);
            auto pts = (frame->pts == AV_NOPTS_VALUE) ? NAN : frame->pts * av_q2d(time_base);
            ret = frame_add(frame, pts, duration, pkt_serial);
#ifdef CONFIG_AVFILTER
            if (*d->packets->serial() != d->decoder->pkt_serial())
                break;
        }
#endif
    }
    av_frame_free(&frame);
}

bool HFFVideoStreamsControl::is_frame_drop()
{
    Q_D(HFFVideoStreamsControl);
    if (d->frame_drop > 0)
        return true;
    if (d->frame_drop == 0)
        return false;
    return d->source->master_sync_type() != HFFSourceControl::SYNC_VIDEO_MASTER;
}

int HFFVideoStreamsControl::decode(AVFrame *frame)
{
    Q_D(HFFVideoStreamsControl);
    auto ret = d->decoder->decode(d->packets, frame, nullptr);
    if (ret < 0)
        return -1;
    if (ret == 0)
        return 0;

    frame->sample_aspect_ratio = av_guess_sample_aspect_ratio(d->fmt_ctx, d->stream, frame);
    if (is_frame_drop() && frame->pts != AV_NOPTS_VALUE && d->packets->remaining())
    {
        double diff = av_q2d(d->stream->time_base) * frame->pts - d->source->master_clock();
        if (!isnan(diff) && fabs(diff) < AV_SYNC_THRESHOLD_NO && diff - d->frame_last_filter_delay < 0 )
        {
            d->frame_drops_early++;
            av_frame_unref(frame);
            return 0;
        }
    }
    return 1;
}

int HFFVideoStreamsControl::frame_add(AVFrame *frame, double pts, double duration, int serial)
{
#ifdef DEBUG_SYNC
    printf("frame_type=%c pts=%0.3f\n", av_get_picture_type_char(frame->pict_type), pts);
#endif

    Q_D(HFFVideoStreamsControl);

    auto vp = d->frames->peek_writeable();
    if (vp == nullptr)
        return -1;

    vp->sar = frame->sample_aspect_ratio;
    vp->uploaded = false;
    vp->width = frame->width;
    vp->height = frame->height;
    vp->format = frame->format;
    vp->pts = pts;
    vp->duration = duration;
    vp->pos = frame->pkt_pos;
    vp->serial = serial;
    av_frame_move_ref(vp->frame, frame);
    d->source->set_default_window_size(vp->width, vp->height, vp->sar);
    d->frames->push();
    av_frame_unref(frame);
    return 1;
}

double HFFVideoStreamsControl::compute_frame_duration(HFFFrame *current, HFFFrame *next)
{
    Q_D(HFFVideoStreamsControl);
    if (current->serial != next->serial)
        return 0.0;
    auto duration = next->pts - current->pts;
    if (isnan(duration) || duration <= 0 || duration > d->max_frame_duration)
        return current->duration;
    return duration;
}

double HFFVideoStreamsControl::compute_target_delay(double delay)
{
    Q_D(HFFVideoStreamsControl);
    double threshold, diff = 0.0;
    // update delay to follow master synchronisation source
    if (d->source->master_sync_type() != HFFSourceControl::SYNC_VIDEO_MASTER)
    {
        // if video is slave, we try to correct big delays by duplicating or deleting a frame
        diff = d->source->clock_diff(HFFSourceControl::SYNC_VIDEO_MASTER);
        // skip or repeat frame. We take into account the delay to compute the threshold.
        // I still don't know if it is the best guess.
        threshold = FFMAX(AV_SYNC_THRESHOLD_MIN, FFMIN(AV_SYNC_THRESHOLD_MAX, delay));
        if (!isnan(diff) && fabs(diff) < d->max_frame_duration)
        {
            if (diff <= -threshold)
                delay = FFMAX(0, delay + diff);
            else if (diff >= threshold && delay > AV_SYNC_FRAMEDUP_THRESHOLD)
                delay = delay + diff;
            else if (diff >= threshold)
                delay = 2 * delay;
        }
    }
    av_log(nullptr, AV_LOG_TRACE, "video: delay=%0.3f A-V=%f\n", delay, -diff);
    return delay;
}

#ifdef CONFIG_AVFILTER
bool HFFVideoStreamsControl::configure_filters(const QString &filters, AVFrame *frame)
{
    Q_D(HFFVideoStreamsControl);

    avfilter_graph_free(&d->filter_graph);
    d->filter_graph = avfilter_graph_alloc();
    if (!d->filter_graph)
        return false;

    char sws_flags[512] = "";
    char scr_args[256];
    AVFilterContext *filter_src = nullptr;
    AVFilterContext *filter_out = nullptr;
    AVFilterContext *filter_last = nullptr;
    auto codecpar = d->stream->codecpar;
    auto frame_rate = av_guess_frame_rate(d->fmt_ctx, d->stream, nullptr);
    AVDictionaryEntry *e = nullptr;

    d->filter_graph->nb_threads = d->filter_nbthreads;
    while ((e = av_dict_get(sws_opts, "", e, AV_DICT_IGNORE_SUFFIX)))
    {
        if (!strcmp(e->key, "sws_flags"))
            av_strlcatf(sws_flags, sizeof(sws_flags), "%s=%s:", "flags", e->value);
        else
            av_strlcatf(sws_flags, sizeof(sws_flags), "%s=%s:", e->key, e->value);
    }
    if (strlen(sws_flags))
        sws_flags[strlen(sws_flags)-1] = '\0';

    d->filter_graph->scale_sws_opts = av_strdup(sws_flags);

    snprintf(scr_args, sizeof(scr_args),
             "video_size=%dx%d:pix_fmt=%d:time_base=%d/%d:pixel_aspect=%d/%d",
             frame->width, frame->height, frame->format,
             d->stream->time_base.num, d->stream->time_base.den,
             codecpar->sample_aspect_ratio.num, FFMAX(codecpar->sample_aspect_ratio.den, 1));
    if (frame_rate.num && frame_rate.den)
        av_strlcatf(scr_args, sizeof(scr_args), ":frame_rate=%d/%d", frame_rate.num, frame_rate.den);

    if (avfilter_graph_create_filter(&filter_src, avfilter_get_by_name("buffer"), "ffplay_buffer", scr_args, nullptr, d->filter_graph) < 0)
        return false;
    if (avfilter_graph_create_filter(&filter_out, avfilter_get_by_name("buffersink"), "ffplay_buffersink", nullptr, nullptr, d->filter_graph) < 0)
        return false;
    if (av_opt_set_int_list(filter_out, "pix_fmts", d->pix_fmts,  AV_PIX_FMT_NONE, AV_OPT_SEARCH_CHILDREN) < 0)
        return false;

    filter_last = filter_out;

// Note: this macro adds a filter before the lastly added filter, so the
// processing order of the filters is in reverse.
#define INSERT_FILT(name, args) do {                                                        \
    AVFilterContext *filter;                                                                \
    if (avfilter_graph_create_filter(&filter, avfilter_get_by_name(name),                   \
                                    "ffplay_" name, args, nullptr, d->filter_graph) < 0)    \
        return false;                                                                       \
    if (avfilter_link(filter, 0, filter_last, 0) < 0)                                       \
        return false;                                                                       \
    filter_last = filter;                                                                   \
} while (0)

    if (d->auto_rotate)
    {
        auto theta  = get_rotation(d->stream);
        if (fabs(theta - 90) < 1.0)
        {
            INSERT_FILT("transpose", "clock");
        }
        else if (fabs(theta - 180) < 1.0)
        {
            INSERT_FILT("hflip", nullptr);
            INSERT_FILT("vflip", nullptr);
        }
        else if (fabs(theta - 270) < 1.0)
        {
            INSERT_FILT("transpose", "cclock");
        }
        else if (fabs(theta) > 1.0)
        {
            char rotate_buf[64];
            snprintf(rotate_buf, sizeof(rotate_buf), "%f*PI/180", theta);
            INSERT_FILT("rotate", rotate_buf);
        }
    }

    if (!configure_filter_graph(d->filter_graph, filters, filter_src, filter_last))
        return false;

    d->filter_in  = filter_src;
    d->filter_out = filter_out;
    return true;
}
#endif

HFFAudioStreamsControl::HFFAudioStreamsControl(HFFSourceControl *source) :
    HFFStreamsControl(*new HFFAudioStreamsControlPrivate, source)
{
}

HFFAudioStreamsControl::~HFFAudioStreamsControl()
{
}

void HFFAudioStreamsControl::frame_handle(bool paused, bool display, uint8_t *stream, int len, int min_buf_size)
{
    Q_D(HFFAudioStreamsControl);
    int size, len1;

    d->callback_time = av_gettime_relative();
    while (len > 0)
    {
        if (d->buf_index >= d->buf_size)
        {
            size = paused ? -1 : decode();
            if (size < 0)
            {
                // if error, just output silence
                d->buf = nullptr;
                d->buf_size = min_buf_size;
            }
            else
            {
                if (display)
                    update_sample_display((int16_t *)d->buf, size);
                d->buf_size = size;
            }
            d->buf_index = 0;
        }
        len1 = d->buf_size - d->buf_index;
        if (len1 > len)
            len1 = len;
        d->source->audio_fill_stream(stream, d->buf, d->buf_index, len1);
        len -= len1;
        stream += len1;
        d->buf_index += len1;
    }
    d->buf_write_size = d->buf_size - d->buf_index;
    // Let's assume the audio driver that is used by SDL has two periods.
    if (!isnan(d->clock))
        d->source->update_audio_pts(d->clock - (2.0 * d->hw_buf_size + d->buf_write_size) / d->tgt.bytes_per_sec, d->clock_serial, d->callback_time / 1000000.0);
}

void HFFAudioStreamsControl::display(bool paused, bool show_wave, QRect rect)
{
    Q_D(HFFAudioStreamsControl);
    int rdft_bits, freq, i_start;
    for (rdft_bits = 1; (1 << rdft_bits) < 2 * rect.height(); rdft_bits++);
    freq = 1 << (rdft_bits - 1);
    i_start = compute_i_start(paused, show_wave, show_wave ? rect.width() : (2 * freq));

    if (show_wave)
        d->source->audio_upload(rect, d->tgt.channels, d->sample, i_start, SAMPLE_ARRAY_SIZE);
    else
    {
        auto channels = FFMIN(d->tgt.channels, 2);
        if (rdft_bits != d->rdft_bits)
        {
            av_rdft_end(d->rdft);
            av_free(d->rdft_data);
            d->rdft = av_rdft_init(rdft_bits, DFT_R2C);
            d->rdft_bits = rdft_bits;
            d->rdft_data = (FFTSample *)av_malloc_array(freq, 4 *sizeof(*d->rdft_data));
        }
        if (!d->rdft || !d->rdft_data)
        {
            av_log(nullptr, AV_LOG_ERROR, "Failed to allocate buffers for RDFT, switching to waves display\n");
            return;
        }

        int i, ch, x;
        double w;
        FFTSample *data[2];
        for (ch = 0; ch < channels; ch++)
        {
            data[ch] = d->rdft_data + 2 * freq * ch;
            i = i_start + ch;
            for (x = 0; x < 2 * freq; x++)
            {
                w = (x - freq) * 1.0 / freq;
                data[ch][x] = d->sample[i] * (1.0 - w * w);
                i += channels;
                if (i >= SAMPLE_ARRAY_SIZE)
                    i -= SAMPLE_ARRAY_SIZE;
            }
            av_rdft_calc(d->rdft, data[ch]);
        }
        d->source->audio_upload(rect, channels, freq, data, d->xpos);
        if (!paused)
            d->xpos++;
        if (d->xpos >= rect.width())
            d->xpos= rect.x();
    }
}

void HFFAudioStreamsControl::switch_channel(AVProgram *p)
{
    Q_D(HFFAudioStreamsControl);
    auto start_index = d->stream_last;
    auto old_index = d->stream_index;
    auto stream_index = start_index;
    auto nb_streams = d->fmt_ctx->nb_streams;

    if (p)
    {
        nb_streams = p->nb_stream_indexes;
        for (start_index = 0; start_index < nb_streams; start_index++)
            if (p->stream_index[start_index] == stream_index)
                break;
        if (start_index == nb_streams)
            start_index = -1;
        stream_index = start_index;
    }

    while (true)
    {
        if (++stream_index >= nb_streams)
        {
            if (start_index == -1)
                return;
            stream_index = 0;
        }
        if (stream_index == start_index)
            return;
        auto st = d->fmt_ctx->streams[p ? p->stream_index[stream_index] : stream_index];
        if (st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO && st->codecpar->sample_rate != 0 && st->codecpar->channels != 0)
            break;
    }

    if (p && stream_index != -1)
        stream_index = p->stream_index[stream_index];

    av_log(nullptr, AV_LOG_INFO, "Switch %s stream from #%d to #%d\n", av_get_media_type_string(AVMEDIA_TYPE_AUDIO), old_index, stream_index);
    close();
    open(stream_index, d->fmt_ctx);
}

bool HFFAudioStreamsControl::open_else()
{
    Q_D(HFFAudioStreamsControl);
    int sample_rate, nb_channels;
    int64_t channel_layout;

#ifdef CONFIG_AVFILTER
    d->filter_src.freq           = d->codec_ctx->sample_rate;
    d->filter_src.channels       = d->codec_ctx->channels;
    d->filter_src.channel_layout = get_valid_channel_layout(d->codec_ctx->channel_layout, d->codec_ctx->channels);
    d->filter_src.format         = d->codec_ctx->sample_fmt;
    if (!configure_filters(d->filters, false))
        return false;
    auto sink = d->filter_out;
    sample_rate    = av_buffersink_get_sample_rate(sink);
    nb_channels    = av_buffersink_get_channels(sink);
    channel_layout = av_buffersink_get_channel_layout(sink);
#else
    sample_rate    = d->codec_ctx->sample_rate;
    nb_channels    = d->codec_ctx->channels;
    channel_layout = d->codec_ctx->channel_layout;
#endif
    d->hw_buf_size = d_ptr->source->audio_open(channel_layout, nb_channels, sample_rate, &d->tgt);
    if (d->hw_buf_size < 0)
        return false;
    d->src = d->tgt;
    d->buf_size  = 0;
    d->buf_index = 0;
    d->clock = 0;
    d->clock_serial = -1;
    // init averaging filter
    d->diff_cum = 0.0;
    d->diff_avg_coef  = exp(log(0.01) / AUDIO_DIFF_AVG_NB);
    d->diff_avg_count = 0;
    // since we do not have a precise anough audio FIFO fullness, we correct audio sync only if larger than this threshold
    d->diff_threshold = 1.0 * d->hw_buf_size / d->tgt.bytes_per_sec;
    d->sample_index = 0;
    d->last_i_start = 0;
    d->rdft_bits = 0;
    d->xpos = 0;
    return true;
}

void HFFAudioStreamsControl::close_else()
{
    Q_D(HFFAudioStreamsControl);
    swr_free(&d->swr_ctx);
    av_freep(&d->buf1);
    d->buf1_size = 0;
    d->buf = nullptr;
    if (d->rdft)
    {
        av_rdft_end(d->rdft);
        av_freep(&d->rdft_data);
        d->rdft = nullptr;
        d->rdft_bits = 0;
    }

#ifdef CONFIG_AVFILTER
    if (d->filter_graph)
        avfilter_graph_free(&d->filter_graph);
#endif
}

void HFFAudioStreamsControl::run()
{
    Q_D(HFFAudioStreamsControl);
    auto frame = av_frame_alloc();
    if (!frame)
        return;

    int ret = 0;
    int pkt_serial = -1;
    AVRational time_base;
#if CONFIG_AVFILTER
    int last_serial = -1;
    int64_t dec_channel_layout;
#endif

    while (ret >= 0)
    {
        auto ret = d->decoder->decode(d->packets, frame, nullptr);
        if (ret < 0)
            break;
        if (ret == 0)
            continue;

        pkt_serial = d->decoder->pkt_serial();
        time_base = (AVRational){1, frame->sample_rate};
#if CONFIG_AVFILTER
        dec_channel_layout = get_valid_channel_layout(frame->channel_layout, frame->channels);
        if (cmp_audio_fmts(d->filter_src.format, d->filter_src.channels, (AVSampleFormat)frame->format, frame->channels) ||
            d->filter_src.channel_layout != dec_channel_layout ||
            d->filter_src.freq != frame->sample_rate ||
            pkt_serial != last_serial)
        {
            char buf1[1024], buf2[1024];
            av_get_channel_layout_string(buf1, sizeof(buf1), -1, d->filter_src.channel_layout);
            av_get_channel_layout_string(buf2, sizeof(buf2), -1, dec_channel_layout);
            av_log(nullptr, AV_LOG_DEBUG,
                   "Audio frame changed from rate:%d ch:%d fmt:%s layout:%s serial:%d to rate:%d ch:%d fmt:%s layout:%s serial:%d\n",
                   d->filter_src.freq, d->filter_src.channels, av_get_sample_fmt_name(d->filter_src.format), buf1, last_serial,
                   frame->sample_rate, frame->channels, av_get_sample_fmt_name((AVSampleFormat)frame->format), buf2, pkt_serial);

            d->filter_src.format         = (AVSampleFormat)frame->format;
            d->filter_src.channels       = frame->channels;
            d->filter_src.channel_layout = dec_channel_layout;
            d->filter_src.freq           = frame->sample_rate;
            last_serial                  = pkt_serial;
            if (!configure_filters(d->filters, true))
                break;
        }

        if (av_buffersrc_add_frame(d->filter_in, frame) < 0)
            break;

        while (ret >= 0)
        {
            ret = av_buffersink_get_frame_flags(d->filter_out, frame, 0);
            if (ret < 0)
            {
                if (ret == AVERROR_EOF)
                    d->decoder->set_finish();
                ret = 0;
                break;
            }
            time_base = av_buffersink_get_time_base(d->filter_out);
#endif
            auto duration = av_q2d((AVRational){frame->nb_samples, frame->sample_rate});
            auto pts = (frame->pts == AV_NOPTS_VALUE) ? NAN : frame->pts * av_q2d(time_base);
            ret = frame_add(frame, duration, pts, pkt_serial);
            av_frame_unref(frame);
#if CONFIG_AVFILTER
            if (*d->packets->serial() != pkt_serial)
                break;
        }
#endif
    }
    av_frame_free(&frame);
}

int HFFAudioStreamsControl::decode()
{
    Q_D(HFFAudioStreamsControl);
    int resampled_data_size;
    HFFFrame *frame;

    do
    {
        while (frame_remaining() == 0)
        {
            if (av_gettime_relative() - d->callback_time > 1000000LL * d->hw_buf_size / d->tgt.bytes_per_sec / 2)
                return -1;
            av_usleep (1000);
        }
        frame = d->frames->peek_readable();
        if (frame == nullptr)
            return -1;
        frame_next();
    } while (frame->serial != *packets_serial());

    int data_size = av_samples_get_buffer_size(nullptr, frame->frame->channels, frame->frame->nb_samples, (AVSampleFormat)frame->frame->format, 1);
    int64_t dec_channel_layout = frame->frame->channel_layout && frame->frame->channels == av_get_channel_layout_nb_channels(frame->frame->channel_layout) ? frame->frame->channel_layout : av_get_default_channel_layout(frame->frame->channels);
    int wanted_nb_samples = synchronize(frame->frame->nb_samples);

    if (frame->frame->format        != d->src.format         ||
        dec_channel_layout          != d->src.channel_layout ||
        frame->frame->sample_rate   != d->src.freq           ||
        (wanted_nb_samples          != frame->frame->nb_samples && !d->swr_ctx))
    {
        swr_free(&d->swr_ctx);
        d->swr_ctx = swr_alloc_set_opts(nullptr,
                                        d->tgt.channel_layout, d->tgt.format, d->tgt.freq,
                                        dec_channel_layout, (AVSampleFormat)frame->frame->format, frame->frame->sample_rate,
                                        0, nullptr);
        if (!d->swr_ctx || swr_init(d->swr_ctx) < 0)
        {
            av_log(nullptr, AV_LOG_ERROR,
                   "Cannot create sample rate converter for conversion of %d Hz %s %d channels to %d Hz %s %d channels!\n",
                   frame->frame->sample_rate, av_get_sample_fmt_name((AVSampleFormat)frame->frame->format), frame->frame->channels,
                   d->tgt.freq, av_get_sample_fmt_name(d->tgt.format), d->tgt.channels);
            swr_free(&d->swr_ctx);
            return -1;
        }
        d->src.channel_layout = dec_channel_layout;
        d->src.channels       = frame->frame->channels;
        d->src.freq           = frame->frame->sample_rate;
        d->src.format         = (AVSampleFormat)frame->frame->format;
    }

    if (d->swr_ctx)
    {
        const uint8_t **in = (const uint8_t **)frame->frame->extended_data;
        uint8_t **out = &d->buf1;
        int out_count = (int64_t)wanted_nb_samples * d->tgt.freq / frame->frame->sample_rate + 256;
        int out_size  = av_samples_get_buffer_size(nullptr, d->tgt.channels, out_count, d->tgt.format, 0);
        if (out_size < 0)
        {
            av_log(nullptr, AV_LOG_ERROR, "av_samples_get_buffer_size() failed\n");
            return -1;
        }
        if (wanted_nb_samples != frame->frame->nb_samples)
        {
            if (swr_set_compensation(d->swr_ctx, (wanted_nb_samples - frame->frame->nb_samples) * d->tgt.freq / frame->frame->sample_rate, wanted_nb_samples * d->tgt.freq / frame->frame->sample_rate) < 0)
            {
                av_log(nullptr, AV_LOG_ERROR, "swr_set_compensation() failed\n");
                return -1;
            }
        }
        av_fast_malloc(&d->buf1, &d->buf1_size, out_size);
        if (!d->buf1)
            return AVERROR(ENOMEM);
        auto len = swr_convert(d->swr_ctx, out, out_count, in, frame->frame->nb_samples);
        if (len < 0)
        {
            av_log(nullptr, AV_LOG_ERROR, "swr_convert() failed\n");
            return -1;
        }
        if (len == out_count)
        {
            av_log(nullptr, AV_LOG_WARNING, "audio buffer is probably too small\n");
            if (swr_init(d->swr_ctx) < 0)
                swr_free(&d->swr_ctx);
        }
        d->buf = d->buf1;
        resampled_data_size = len * d->tgt.channels * av_get_bytes_per_sample(d->tgt.format);
    }
    else
    {
        d->buf = frame->frame->data[0];
        resampled_data_size = data_size;
    }

    // update the audio clock with the pts
    d->clock = isnan(frame->pts) ? NAN : frame->pts + 1.0 * frame->frame->nb_samples / frame->frame->sample_rate;
    d->clock_serial = frame->serial;
    return resampled_data_size;
}

int HFFAudioStreamsControl::synchronize(int nb_samples)
{
    Q_D(HFFAudioStreamsControl);
    int wanted_nb_samples = nb_samples;

    // if not master, then we try to remove or add samples to correct the clock
    if (d->source->master_sync_type() != HFFSourceControl::SYNC_AUDIO_MASTER)
    {
        auto diff = d->source->clock_diff(HFFSourceControl::SYNC_AUDIO_MASTER);
        if (!isnan(diff) && fabs(diff) < AV_SYNC_THRESHOLD_NO)
        {
            d->diff_cum = diff + d->diff_avg_coef * d->diff_cum;
            if (d->diff_avg_count < AUDIO_DIFF_AVG_NB)
            {
                // not enough measures to have a correct estimate
                d->diff_avg_count++;
            }
            else
            {
                // estimate the A-V difference
                auto avg_diff = d->diff_cum * (1.0 - d->diff_avg_coef);
                if (fabs(avg_diff) >= d->diff_threshold)
                {
                    wanted_nb_samples = nb_samples + (int)(diff * d->src.freq);
                    auto min = ((nb_samples * (100 - SAMPLE_CORRECTION_PERCENT_MAX) / 100));
                    auto max = ((nb_samples * (100 + SAMPLE_CORRECTION_PERCENT_MAX) / 100));
                    wanted_nb_samples = av_clip(wanted_nb_samples, min, max);
                }
                av_log(nullptr, AV_LOG_TRACE, "diff=%f adiff=%f sample_diff=%d apts=%0.3f %f\n",
                       diff, avg_diff, wanted_nb_samples - nb_samples,
                       d->clock, d->diff_threshold);
            }
        }
        else
        {
            // too big difference : may be initial PTS errors, so reset A-V filter
            d->diff_avg_count = 0;
            d->diff_cum = 0;
        }
    }
    return wanted_nb_samples;
}

void HFFAudioStreamsControl::update_sample_display(short *samples, int samples_size)
{
    Q_D(HFFAudioStreamsControl);
    int size, len;

    size = samples_size / sizeof(short);
    while (size > 0)
    {
        len = SAMPLE_ARRAY_SIZE - d->sample_index;
        if (len > size)
            len = size;
        memcpy(d->sample + d->sample_index, samples, len * sizeof(short));
        samples += len;
        d->sample_index += len;
        if (d->sample_index >= SAMPLE_ARRAY_SIZE)
            d->sample_index = 0;
        size -= len;
    }
}

int HFFAudioStreamsControl::frame_add(AVFrame *frame, double pts, double duration, int serial)
{
    Q_D(HFFAudioStreamsControl);

    auto vp = d->frames->peek_writeable();
    if (vp == nullptr)
        return -1;

    vp->pts = pts;
    vp->pos = frame->pkt_pos;
    vp->serial = serial;
    vp->duration = duration;
    av_frame_move_ref(vp->frame, frame);
    d->frames->push();
    av_frame_unref(frame);
    return 1;
}

int HFFAudioStreamsControl::compute_i_start(bool paused, bool show_wave, int data_used)
{
    Q_D(HFFAudioStreamsControl);
    if (paused)
        return d->last_i_start;

    int channels = d->tgt.channels;
    int delay = d->buf_write_size / (channels * 2);

    // to be more precise, we take into account the time spent since the last buffer computation
    if (d->callback_time)
        delay -= ((av_gettime_relative() - d->callback_time) * d->tgt.freq) / 1000000;

    delay += 2 * data_used;
    if (delay < data_used)
        delay = data_used;

    auto i_start = cmp_mod(d->sample_index - delay * channels, SAMPLE_ARRAY_SIZE);
    if (show_wave)
    {
        auto x = i_start;
        auto h = INT_MIN;
        for (int i = 0; i < 1000; i += channels)
        {
            int idx = (SAMPLE_ARRAY_SIZE + x - i) % SAMPLE_ARRAY_SIZE;
            int t1 = d->sample[idx];
            int t2 = d->sample[(idx + 4 * channels) % SAMPLE_ARRAY_SIZE];
            int t3 = d->sample[(idx + 5 * channels) % SAMPLE_ARRAY_SIZE];
            int t4 = d->sample[(idx + 9 * channels) % SAMPLE_ARRAY_SIZE];
            int score = t1 - t4;
            if (h < score && (t2 ^ t3) < 0)
            {
                h = score;
                i_start = idx;
            }
        }
    }
    d->last_i_start = i_start;
    return d->last_i_start;
}

#ifdef CONFIG_AVFILTER
bool HFFAudioStreamsControl::configure_filters(const QString &filters, bool force_output_format)
{
    Q_D(HFFAudioStreamsControl);

    avfilter_graph_free(&d->filter_graph);
    d->filter_graph = avfilter_graph_alloc();
    if (!d->filter_graph)
        return false;

    char aresample_swr_opts[512] = "";
    char src_args[256];
    AVFilterContext *filter_src = nullptr;
    AVFilterContext *filter_sink = nullptr;
    AVDictionaryEntry *e = nullptr;

    d->filter_graph->nb_threads = d->filter_nbthreads;
    while ((e = av_dict_get(swr_opts, "", e, AV_DICT_IGNORE_SUFFIX)))
        av_strlcatf(aresample_swr_opts, sizeof(aresample_swr_opts), "%s=%s:", e->key, e->value);
    if (strlen(aresample_swr_opts))
        aresample_swr_opts[strlen(aresample_swr_opts)-1] = '\0';
    av_opt_set(d->filter_graph, "aresample_swr_opts", aresample_swr_opts, 0);

    auto ret = snprintf(src_args, sizeof(src_args),
                        "sample_rate=%d:sample_fmt=%s:channels=%d:time_base=%d/%d",
                        d->filter_src.freq, av_get_sample_fmt_name(d->filter_src.format),
                        d->filter_src.channels,
                        1, d->filter_src.freq);
    if (d->filter_src.channel_layout)
        snprintf(src_args + ret, sizeof(src_args) - ret, ":channel_layout=0x%I64x",  d->filter_src.channel_layout);

    if (avfilter_graph_create_filter(&filter_src, avfilter_get_by_name("abuffer"), "ffplay_abuffer", src_args, nullptr, d->filter_graph) < 0)
        return false;
    if (avfilter_graph_create_filter(&filter_sink, avfilter_get_by_name("abuffersink"), "ffplay_abuffersink", nullptr, nullptr, d->filter_graph) < 0)
        return false;
    if (av_opt_set_int_list(filter_sink, "sample_fmts", d->sample_fmts,  AV_SAMPLE_FMT_NONE, AV_OPT_SEARCH_CHILDREN) < 0)
        return false;
    if (av_opt_set_int(filter_sink, "all_channel_counts", 1, AV_OPT_SEARCH_CHILDREN) < 0)
        return false;
    if (force_output_format)
    {
        int64_t channel_layouts[2] = { d->tgt.channel_layout, -1 };
        int channels[2] = { d->tgt.channels, -1 };
        int sample_rates[2] = { d->tgt.freq, -1 };
        if (av_opt_set_int(filter_sink, "all_channel_counts", 0, AV_OPT_SEARCH_CHILDREN) < 0)
            return false;
        if (av_opt_set_int_list(filter_sink, "channel_layouts", channel_layouts,  -1, AV_OPT_SEARCH_CHILDREN) < 0)
            return false;
        if (av_opt_set_int_list(filter_sink, "channel_counts" , channels, -1, AV_OPT_SEARCH_CHILDREN) < 0)
            return false;
        if (av_opt_set_int_list(filter_sink, "sample_rates"   , sample_rates   ,  -1, AV_OPT_SEARCH_CHILDREN) < 0)
            return false;
    }

    if (!configure_filter_graph(d->filter_graph, filters, filter_src, filter_sink))
        return false;
    d->filter_in  = filter_src;
    d->filter_out = filter_sink;
    return true;
}
#endif

HFFSubtitleStreamsControl::HFFSubtitleStreamsControl(HFFSourceControl *source) :
    HFFStreamsControl(*new HFFSubtitleStreamsControlPrivate, source)
{
}

HFFSubtitleStreamsControl::~HFFSubtitleStreamsControl()
{
}

int HFFSubtitleStreamsControl::frame_handle(double pts)
{
    Q_D(HFFSubtitleStreamsControl);
    HFFFrame *frame = d->frames->peek();
    HFFFrame *frame_next = nullptr;

    if (d->frames->remaining() > 1)
        frame_next = d->frames->peek_next();

    if (frame->serial != *packets_serial() ||
        pts > frame->pts + frame->sub.end_display_time / 1000.0 ||
        (frame_next && pts > frame_next->pts + frame_next->sub.start_display_time / 1000.0))
    {
        if (frame->uploaded)
            d->source->subtitle_upload(frame);
        return 1;
    }
    return -1;
}

HFFFrame *HFFSubtitleStreamsControl::display(double pts, int width, int height)
{
    Q_D(HFFSubtitleStreamsControl);
    if (d_ptr->stream_index < 0 || frame_remaining() <= 0)
        return nullptr;
    auto frame = d->frames->peek();
    if (pts < frame->pts + frame->sub.start_display_time / 1000.0)
        return nullptr;
    if (!frame->uploaded)
    {
        if (!frame->width || !frame->height)
        {
            frame->width = width;
            frame->height = height;
        }
        d->source->subtitle_upload(frame);
    }
    return frame;
}

void HFFSubtitleStreamsControl::switch_channel(AVProgram *p)
{
    Q_D(HFFSubtitleStreamsControl);
    auto start_index = d->stream_last;
    auto old_index = d->stream_index;
    auto stream_index = start_index;
    auto nb_streams = d->fmt_ctx->nb_streams;

    if (p)
    {
        nb_streams = p->nb_stream_indexes;
        for (start_index = 0; start_index < nb_streams; start_index++)
            if (p->stream_index[start_index] == stream_index)
                break;
        if (start_index == nb_streams)
            start_index = -1;
        stream_index = start_index;
    }

    while (true)
    {
        if (++stream_index >= nb_streams)
        {
            stream_index = -1;
            d->stream_last = -1;
            break;
        }
        if (stream_index == start_index)
            return;
        auto st = d->fmt_ctx->streams[p ? p->stream_index[stream_index] : stream_index];
        if (st->codecpar->codec_type == AVMEDIA_TYPE_SUBTITLE)
            break;
    }

    if (p && stream_index != -1)
        stream_index = p->stream_index[stream_index];

    av_log(nullptr, AV_LOG_INFO, "Switch %s stream from #%d to #%d\n", av_get_media_type_string(AVMEDIA_TYPE_SUBTITLE), old_index, stream_index);
    close();
    open(stream_index, d->fmt_ctx);
}

bool HFFSubtitleStreamsControl::open_else()
{
    return true;
}

void HFFSubtitleStreamsControl::close_else()
{

}

void HFFSubtitleStreamsControl::run()
{
    Q_D(HFFSubtitleStreamsControl);
    int ret = 0;
    HFFFrame *frame;
    while (ret >= 0)
    {
        frame = d->frames->peek_writeable();
        if (frame == nullptr)
            return;
        ret = d->decoder->decode(d->packets, nullptr, &frame->sub);
        if (ret < 0)
            return;
        if (ret == 0)
            continue;

        if (frame->sub.format == 0)
        {
            frame->pts = frame->sub.pts != AV_NOPTS_VALUE ? 1.0 * frame->sub.pts / AV_TIME_BASE : 0.0;
            frame->serial = d->decoder->pkt_serial();
            frame->width = d->codec_ctx->width;
            frame->height = d->codec_ctx->height;
            frame->uploaded = false;
            d->frames->push();
        }
        else
            avsubtitle_free(&frame->sub);
    }
}

HE_CONTROL_END_NAMESPACE
