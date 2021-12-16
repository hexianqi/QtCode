#include "HFFCmdUtil.h"
#include "HFFmpeg.h"

extern "C" {
#include "libavutil/display.h"
}

HE_BEGIN_NAMESPACE

AVDictionary *format_opts;
AVDictionary *codec_opts;
AVDictionary *resample_opts;
AVDictionary *sws_opts;
AVDictionary *swr_opts;
AVPacket flush_pkt;

void init_opts()
{
    av_dict_set(&sws_opts, "flags", "bicubic", 0);
}

void uninit_opts()
{
    av_dict_free(&swr_opts);
    av_dict_free(&sws_opts);
    av_dict_free(&format_opts);
    av_dict_free(&codec_opts);
    av_dict_free(&resample_opts);
}

int check_stream_specifier(AVFormatContext *ctx, AVStream *st, const char *spec)
{
    int ret = avformat_match_stream_specifier(ctx, st, spec);
    if (ret < 0)
        av_log(ctx, AV_LOG_ERROR, "Invalid stream specifier: %s.\n", spec);
    return ret;
}

AVDictionary *filter_codec_opts(AVDictionary *opts, AVCodecID codec_id, AVFormatContext *ctx, AVStream *st, AVCodec *codec)
{
    AVDictionary *ret = nullptr;
    AVDictionaryEntry *t = nullptr;
    char prefix = 0;
    auto cc = avcodec_get_class();
    auto flags = ctx->oformat ? AV_OPT_FLAG_ENCODING_PARAM : AV_OPT_FLAG_DECODING_PARAM;

    if (!codec)
        codec = ctx->oformat ? avcodec_find_encoder(codec_id) : avcodec_find_decoder(codec_id);

    switch (st->codecpar->codec_type)
    {
    case AVMEDIA_TYPE_VIDEO:
        prefix  = 'v';
        flags  |= AV_OPT_FLAG_VIDEO_PARAM;
        break;
    case AVMEDIA_TYPE_AUDIO:
        prefix  = 'a';
        flags  |= AV_OPT_FLAG_AUDIO_PARAM;
        break;
    case AVMEDIA_TYPE_SUBTITLE:
        prefix  = 's';
        flags  |= AV_OPT_FLAG_SUBTITLE_PARAM;
        break;
    default:
        break;
    }

    while ((t = av_dict_get(opts, "", t, AV_DICT_IGNORE_SUFFIX)))
    {
        // check stream specification in opt name
        auto p = strchr(t->key, ':');
        if (p)
        {
            auto temp = check_stream_specifier(ctx, st, p + 1);
            if (temp == 1)
                *p = 0;
            else if (temp == 0)
                continue;
            else
                return nullptr;
        }
        if (av_opt_find(&cc, t->key, nullptr, flags, AV_OPT_SEARCH_FAKE_OBJ) || !codec || (codec->priv_class && av_opt_find(&codec->priv_class, t->key, nullptr, flags, AV_OPT_SEARCH_FAKE_OBJ)))
            av_dict_set(&ret, t->key, t->value, 0);
        else if (t->key[0] == prefix && av_opt_find(&cc, t->key + 1, nullptr, flags, AV_OPT_SEARCH_FAKE_OBJ))
            av_dict_set(&ret, t->key + 1, t->value, 0);

        if (p)
            *p = ':';
    }
    return ret;
}

AVDictionary **setup_find_stream_info_opts(AVFormatContext *ctx, AVDictionary *codec_opts)
{
    if (ctx->nb_streams == 0)
        return nullptr;

    AVDictionary **opts;
    opts = (AVDictionary **)av_mallocz_array(ctx->nb_streams, sizeof(*opts));
    if (!opts)
    {
        av_log(nullptr, AV_LOG_ERROR, "Could not alloc memory for stream options.\n");
        return nullptr;
    }
    for (unsigned int i = 0; i < ctx->nb_streams; i++)
        opts[i] = filter_codec_opts(codec_opts, ctx->streams[i]->codecpar->codec_id, ctx, ctx->streams[i], nullptr);
    return opts;
}

double get_rotation(AVStream *st)
{
    auto matrix = av_stream_get_side_data(st, AV_PKT_DATA_DISPLAYMATRIX, nullptr);
    auto theta = 0.0;
    if (matrix)
        theta = -av_display_rotation_get((int32_t *)matrix);
    theta -= 360 * floor(theta / 360 + 0.9 / 360);
    if (fabs(theta - 90 * round(theta / 90)) > 2)
        av_log(nullptr, AV_LOG_WARNING, "Odd rotation angle.\n"
                                        "If you want to help, upload a sample "
                                        "of this file to https://streams.videolan.org/upload/ "
                                        "and contact the ffmpeg-devel mailing list. (ffmpeg-devel@ffmpeg.org)");
    return theta;
}

bool is_realtime(AVFormatContext *ctx)
{
    if (!strcmp(ctx->iformat->name, "rtp") || !strcmp(ctx->iformat->name, "rtsp") || !strcmp(ctx->iformat->name, "sdp"))
        return true;
    if (ctx->pb && (!strncmp(ctx->url, "rtp:", 4) || !strncmp(ctx->url, "udp:", 4)))
        return true;
    return false;
}

int64_t get_valid_channel_layout(int64_t channel_layout, int channels)
{
    return channel_layout && av_get_channel_layout_nb_channels(channel_layout) == channels ? channel_layout : 0;
}

bool cmp_audio_fmts(AVSampleFormat fmt1, int64_t channel_count1, AVSampleFormat fmt2, int64_t channel_count2)
{
    // If channel count == 1, planar and non-planar formats are the same
    if (channel_count1 == 1 && channel_count2 == 1)
        return av_get_packed_sample_fmt(fmt1) != av_get_packed_sample_fmt(fmt2);
    return channel_count1 != channel_count2 || fmt1 != fmt2;
}

int cmp_mod(int a, int b)
{
    return a < 0 ? a%b + b : a%b;
}

HE_END_NAMESPACE
