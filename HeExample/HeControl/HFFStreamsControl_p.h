#pragma once

#include "HFFStreamsControl.h"
#include "HFFmpeg.h"
#include "HFFTypes.h"

HE_BEGIN_NAMESPACE

class HFFPacketQueue;
class HFFFrameQueue;
class HFFDecoderControl;

class HFFStreamsControlPrivate
{
public:
    int lowres = 0;
    bool fast = false;                      // non spec compliant optimizations
    QString forced_codec_name;              // force decoder

public:
    int stream_index = -1;
    int stream_last = -1;

public:
    HFFSourceControl *source = nullptr;
    AVFormatContext *fmt_ctx = nullptr;
    AVCodecContext *codec_ctx = nullptr;
    AVStream *stream = nullptr;

public:
    QThread *thread = nullptr;
    HFFPacketQueue *packets = nullptr;
    HFFFrameQueue *frames = nullptr;
    HFFDecoderControl *decoder = nullptr;
};

class HFFVideoStreamsControlPrivate : public HFFStreamsControlPrivate
{
public:
    bool auto_rotate = true;                // automatically rotate video
    int frame_drop = -1;                    // drop frames when cpu is too slow [0=off 1=on -1=auto]
    double max_frame_duration = 10.0;       // maximum duration of a frame - above this, we consider the jump a timestamp discontinuity
    AVPixelFormat pix_fmts[100];

public:
    int frame_drops_early = 0;
    int frame_drops_late = 0;
    double frame_timer = 0.0;
    double frame_last_returned_time = 0.0;
    double frame_last_filter_delay = 0.0;

#ifdef CONFIG_AVFILTER
public:
    QStringList filters;
    int filter_nbthreads = 0;                   // number of filter threads per graph
    int filter_idx;
    AVFilterContext *filter_in;                 // the first filter in the video chain
    AVFilterContext *filter_out;                // the last filter in the video chain
    AVFilterGraph *filter_graph = nullptr;      // filter graph
#endif
};

class HFFAudioStreamsControlPrivate : public HFFStreamsControlPrivate
{
public:
    AVSampleFormat sample_fmts[2] = { AV_SAMPLE_FMT_S16, AV_SAMPLE_FMT_NONE };

public:
    int64_t callback_time;
    int hw_buf_size = 0;
    uint32_t buf_index;         // in bytes
    uint32_t buf_size;          // in bytes
    uint32_t buf_write_size;
    uint32_t buf1_size;
    uint8_t *buf;
    uint8_t *buf1;

    double clock;
    int clock_serial;
    double diff_cum;        // used for AV difference average computation
    double diff_avg_coef;
    double diff_threshold;
    int diff_avg_count;

    int16_t sample[SAMPLE_ARRAY_SIZE];
    int sample_index;
    int last_i_start;

    RDFTContext *rdft;
    int rdft_bits;
    FFTSample *rdft_data;
    int xpos;

    SwrContext *swr_ctx = nullptr;
    HFFAudioParams src;
    HFFAudioParams tgt;
#ifdef CONFIG_AVFILTER
public:
    QString filters;
    int filter_nbthreads = 0;               // number of filter threads per graph
    HFFAudioParams filter_src;
    AVFilterContext *filter_in = nullptr;   // the first filter in the audio chain
    AVFilterContext *filter_out = nullptr;  // the last filter in the audio chain
    AVFilterGraph *filter_graph = nullptr;  // filter graph
#endif
};

class HFFSubtitleStreamsControlPrivate : public HFFStreamsControlPrivate
{
};

HE_END_NAMESPACE

