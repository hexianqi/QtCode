#include "HFFmpegUtil.h"
#include "HFFmpeg.h"
#include <QtCore/QMutex>
#include <QtCore/QtDebug>

extern "C" {
#include "libavfilter/buffersrc.h"
#include "libavfilter/buffersink.h"
}

HE_CONTROL_BEGIN_NAMESPACE

bool __initialized = false;
QMutex __mutex;

void HFFmpegUtil::initLib()
{
    if (__initialized)
        return;

    QMutexLocker locker(&__mutex);
    // 注册所有设备，主要用于本地摄像机播放支持
    avdevice_register_all();
    // 初始化网络流格式，使用网络流时必须先执行
    avformat_network_init();
    __initialized = true;
    qDebug() << "Init ffmpeg lib ok.";
}

AVFormatContext *HFFmpegUtil::createFormatContext(QString url, QString formatName, AVDictionary *options)
{
    auto format = formatName.isEmpty() ? nullptr : av_find_input_format(formatName.toStdString().data());
    auto context = avformat_alloc_context();
    if (avformat_open_input(&context, url.toStdString().data(), format, &options) != 0)
    {
        qDebug() << "Couldn't open input stream.";
        return nullptr;
    }
    if (avformat_find_stream_info(context, nullptr) < 0)
    {
        qDebug() << "Couldn't find stream information.";
        avformat_close_input(&context);
        return nullptr;
    }
    return context;
}

AVFormatContext *HFFmpegUtil::createFormatContext(QString url, AVCodecParameters *codecpars)
{
    return createFormatContext(url, QList<AVCodecParameters *>() << codecpars);
}

AVFormatContext *HFFmpegUtil::createFormatContext(QString url, QList<AVCodecParameters *> codecpars)
{
    AVFormatContext *context = nullptr;
    if (avformat_alloc_output_context2(&context, nullptr, nullptr, url.toStdString().data()) < 0)
    {
        qDebug() << "Couldn't create output context.";
        return nullptr;
    }
    for (auto v : codecpars)
    {
        if (v == nullptr)
            continue;
        if (createStream(context, v) == nullptr)
        {
            avformat_free_context(context);
            return nullptr;
        }
    }
    if (!(context->oformat->flags & AVFMT_NOFILE))
    {
        if (avio_open(&context->pb, url.toStdString().data(), AVIO_FLAG_READ_WRITE) < 0)
        {
            qDebug() << "Couldn't open output file.";
            avformat_free_context(context);
            return nullptr;
        }
    }
    return context;
}

AVCodecContext *HFFmpegUtil::createCodecContext(AVFormatContext *formatContext, AVMediaType type, AVDictionary *options, int *index)
{
    AVCodec *decoder = nullptr;
    auto text = av_get_media_type_string(type);
    auto i = av_find_best_stream(formatContext, type, -1, -1, &decoder, 0);
    if (i < 0)
    {
        qDebug() << QString("Couldn't find %1 stream.").arg(text);
        return nullptr;
    }
    if (decoder == nullptr)
    {
        qDebug() << QString("Couldn't find %1 decoder.").arg(text);
        return nullptr;
    }
    auto context = avcodec_alloc_context3(decoder);
    if (context == nullptr)
    {
        qDebug() << QString("Couldn't allocate the %1 codec context.").arg(text);
        return nullptr;
    }
    if (avcodec_parameters_to_context(context, formatContext->streams[i]->codecpar) != 0)
    {
        qDebug() << QString("Couldn't allocate the %1 codec context.").arg(text);
        avcodec_free_context(&context);
        return nullptr;
    }
    if (avcodec_open2(context, nullptr, &options) < 0)
    {
        qDebug() << QString("Couldn't open %1 codec.").arg(text);
        avcodec_free_context(&context);
        return nullptr;
    }
    *index = i;
    return context;
}

AVBSFContext *HFFmpegUtil::createBSFContext(QString name, AVStream *stream)
{
    AVBSFContext *context;
    auto bsf = av_bsf_get_by_name(name.toStdString().data());
    if(!bsf)
    {
        qDebug() << "Unkonw bitstream filter.";
        return nullptr;
    }
    if (av_bsf_alloc(bsf, &context) < 0)
    {
        qDebug() << "Couldn't allocate bsf.";
        return nullptr;
    }
    if (avcodec_parameters_copy(context->par_in, stream->codecpar) < 0)
    {
        qDebug() << "Couldn't copy bsf codecpar.";
        av_bsf_free(&context);
        return nullptr;
    }
    context->time_base_in = stream->time_base;
    av_bsf_init(context);
    return context;
}

QList<AVFilterContext *> HFFmpegUtil::createFilterContext(AVCodecContext *codecContext, AVStream *stream, QString filters)
{
    char args[512] = {};
    AVFilterContext *srcContext;
    AVFilterContext *sinkContext;
    AVPixelFormat pix_fmts[] = { AV_PIX_FMT_YUV420P, AV_PIX_FMT_NONE };
    auto output = avfilter_inout_alloc();
    auto input = avfilter_inout_alloc();
    auto graph = avfilter_graph_alloc();
    if (!output || !input || !graph)
        return {};

    snprintf(args, sizeof(args),
             "video_size=%dx%d:pix_fmt=%d:time_base=%d/%d:pixel_aspect=%d/%d",
             codecContext->width, codecContext->height, codecContext->pix_fmt,
             stream->time_base.num, stream->time_base.den,
             codecContext->sample_aspect_ratio.num, codecContext->sample_aspect_ratio.den);
    if (avfilter_graph_create_filter(&srcContext, avfilter_get_by_name("buffer"), "in", args, nullptr, graph) < 0)
    {
        qDebug() << "Couldn't create buffer source.";
        return {};
    }

    if (avfilter_graph_create_filter(&sinkContext, avfilter_get_by_name("buffersink"), "out", nullptr, nullptr, graph) < 0)
    {
        qDebug() << "Couldn't create buffer sink.";
        return {};
    }
    if (av_opt_set_int_list(sinkContext, "pix_fmts", pix_fmts, AV_PIX_FMT_NONE, AV_OPT_SEARCH_CHILDREN) < 0)
    {
        qDebug() << "Couldn't set output pixel format.";
        return {};
    }

    output->name = av_strdup("in");
    output->filter_ctx = srcContext;
    output->pad_idx = 0;
    output->next = nullptr;
    input->name = av_strdup("out");
    input->filter_ctx = sinkContext;
    input->pad_idx = 0;
    input->next = nullptr;
    if (avfilter_graph_parse_ptr(graph, filters.toStdString().data(), &input, &output, nullptr) < 0)
    {
        qDebug() << "Couldn't parse filter graph.";
        return {};
    }
    if (avfilter_graph_config(graph, nullptr) < 0)
    {
        qDebug() << "Couldn't config filter graph.";
        return {};
    }
    avfilter_inout_free(&input);
    avfilter_inout_free(&output);
    return QList<AVFilterContext *>() << srcContext << sinkContext;
}

AVStream *HFFmpegUtil::createStream(AVFormatContext *formatContext, AVCodecContext *codecContext)
{
    auto stream = avformat_new_stream(formatContext, nullptr);
    if (stream == nullptr)
    {
        qDebug() << "Couldn't create stream.";
        return nullptr;
    }
    if (avcodec_parameters_from_context(stream->codecpar, codecContext) != 0)
    {
        qDebug() << "Couldn't copy codec context.";
        return nullptr;
    }
    return stream;
}

AVStream *HFFmpegUtil::createStream(AVFormatContext *formatContext, AVCodecParameters *codecpar)
{
    auto stream = avformat_new_stream(formatContext, nullptr);
    if (stream == nullptr)
    {
        qDebug() << "Couldn't allocating output stream.";
        return nullptr;
    }
    if (avcodec_parameters_copy(stream->codecpar, codecpar) < 0)
    {
        qDebug() << "Couldn't copy context from input to output stream codec context.";
        return nullptr;
    }
    stream->codecpar->codec_tag = 0;
    return stream;
}

AVFrame *HFFmpegUtil::createFrame(AVPixelFormat format, int width, int height)
{
    auto frame = av_frame_alloc();
    if (frame == nullptr)
        return nullptr;
    frame->format = format;
    frame->width  = width;
    frame->height = height;
    return frame;
}

AVFrame *HFFmpegUtil::createFrame(AVSampleFormat format, int samples)
{
    auto frame = av_frame_alloc();
    if (frame == nullptr)
        return nullptr;
    frame->format = format;
    frame->nb_samples  = samples;
    return frame;
}

bool HFFmpegUtil::decodePacket(AVCodecContext *codecContext, AVPacket *packet, std::function<bool(AVFrame *)> handle)
{
    if (avcodec_send_packet(codecContext, packet) < 0)
    {
        qDebug() << "Decode Error.";
        return false;
    }
    auto frame = av_frame_alloc();
    while (avcodec_receive_frame(codecContext, frame) == 0)
    {
        if (!handle(frame))
            return false;
    }
    av_free(frame);
    return true;
}

bool HFFmpegUtil::encoderPacket(AVCodecContext *codecContext, AVFrame *frame, std::function<bool(AVPacket *)> handle)
{
    // flush encoder
    if (frame == nullptr && !(codecContext->codec->capabilities & AV_CODEC_CAP_DELAY))
        return true;

    if (avcodec_send_frame(codecContext, frame) < 0)
    {
        qDebug() << "Encode Error.";
        return false;
    }
    auto packet = av_packet_alloc();
    av_init_packet(packet);
    while (avcodec_receive_packet(codecContext, packet) == 0)
    {
        if (!handle(packet))
            return false;
        av_packet_unref(packet);
    }
    av_packet_free(&packet);
    return true;
}

bool HFFmpegUtil::filter(QList<AVFilterContext *> filters, AVFrame *frame, std::function<bool(AVFrame *)> handle)
{
    if (av_buffersrc_add_frame_flags(filters.first(), frame, AV_BUFFERSRC_FLAG_KEEP_REF) < 0)
    {
        qDebug() << "Error while feeding the filter graph.";
        return false;
    }
    auto frame2 = av_frame_alloc();
    while (av_buffersink_get_frame(filters.last(), frame2) >= 0)
    {
        if (!handle(frame2))
            return false;
        av_frame_unref(frame2);
    }
    av_free(frame2);
    return true;
}

void HFFmpegUtil::showAllInfo()
{
    qDebug() << "=== Info ===";
    auto info = getVersionInfo();
    for (auto i = info.constBegin(); i != info.constEnd(); i++)
        qDebug() << i.key() << ":" << i.value().toString();
    qDebug() << "=== input protocols ===";
    for (auto p : getProtocol(0))
        qDebug() << p;
    qDebug() << "=== output protocols ===";
    for (auto p : getProtocol(1))
        qDebug() << p;
    qDebug() << "=== demuxer ===";
    for (auto p : getInputFormat())
        qDebug() << p->name;
    qDebug() << "=== muxer ===";
    for (auto p : getOutputFormat())
        qDebug() << p->name;
    qDebug() << "=== encoder ===";
    for (auto p : getEncoder())
        qDebug() << p->name;
    qDebug() << "=== decoder ===";
    for (auto p : getDecoder())
        qDebug() << p->name;
    qDebug() << "=== filter ===";
    for (auto p : getFilter())
        qDebug() << p->name;
    qDebug() << "=== bsf ===";
    for (auto p : getBSF())
        qDebug() << p->name;
}

void HFFmpegUtil::showObjectOpt(void *object)
{
    qDebug() << "Output some option info about object:";
    qDebug() << QString("Object name:%1").arg((*(AVClass **) object)->class_name);
    qDebug() << "Video param:";
    av_opt_show2(object, stderr, AV_OPT_FLAG_VIDEO_PARAM, 0);
    qDebug() << "Audio param:";
    av_opt_show2(object, stderr, AV_OPT_FLAG_AUDIO_PARAM, 0);
    qDebug() << "Decoding param:";
    av_opt_show2(object, stderr, AV_OPT_FLAG_DECODING_PARAM, 0);
    qDebug() << "Encoding param:";
    av_opt_show2(object, stderr, AV_OPT_FLAG_ENCODING_PARAM, 0);
}

QVariantMap HFFmpegUtil::getVersionInfo()
{
    QVariantMap map;
    map.insert("version",       av_version_info());
    map.insert("avutil",        avutil_version());
    map.insert("avcodec",       avcodec_version());
    map.insert("avformat",      avformat_version());
    map.insert("license",       avformat_license());
    map.insert("configuration", avformat_configuration());
    return map;
}

QStringList HFFmpegUtil::getProtocol(int output)
{
    QStringList list;
    void *opaque = nullptr;
    auto *protocol = avio_enum_protocols(&opaque, output);
    while (protocol != nullptr)
    {
        list << protocol;
        protocol = avio_enum_protocols(&opaque, output);
    }
    return list;
}

QList<const AVInputFormat *> HFFmpegUtil::getInputFormat()
{
    QList<const AVInputFormat *> list;
    void *opaque = nullptr;
    auto *format = av_demuxer_iterate(&opaque);
    while (format != nullptr)
    {
        list << format;
        format = av_demuxer_iterate(&opaque);
    }
    return list;
}

QList<const AVOutputFormat *> HFFmpegUtil::getOutputFormat()
{
    QList<const AVOutputFormat *> list;
    void *opaque = nullptr;
    auto *format = av_muxer_iterate(&opaque);
    while (format != nullptr)
    {
        list << format;
        format = av_muxer_iterate(&opaque);
    }
    return list;
}

QList<const AVCodec *> HFFmpegUtil::getCodec(std::function<bool(const AVCodec *)> filter)
{
    QList<const AVCodec *> list;
    void *opaque = nullptr;
    auto *codec = av_codec_iterate(&opaque);
    while (codec != nullptr)
    {
        if (filter == nullptr || filter(codec))
            list << codec;
        codec = av_codec_iterate(&opaque);
    }
    return list;
}

QList<const AVCodec *> HFFmpegUtil::getEncoder()
{
    return getCodec(av_codec_is_encoder);
}

AVCodec *HFFmpegUtil::getEncoder(AVCodecID id)
{
    auto encoder = avcodec_find_encoder(id);
    if (encoder == nullptr)
    {
        qDebug() << QString("Couldn't find encoder for '%1'.").arg(avcodec_get_name(id));
        return nullptr;
    }
    return encoder;
}

QList<const AVCodec *> HFFmpegUtil::getDecoder()
{
    return getCodec(av_codec_is_decoder);
}

QList<const AVFilter *> HFFmpegUtil::getFilter()
{
    QList<const AVFilter *> list;
    void *opaque = nullptr;
    auto *filter = av_filter_iterate(&opaque);
    while (filter != nullptr)
    {
        list << filter;
        filter = av_filter_iterate(&opaque);
    }
    return list;
}

QList<const AVBitStreamFilter *> HFFmpegUtil::getBSF()
{
    QList<const AVBitStreamFilter *> list;
    void *opaque = nullptr;
    auto *bsf = av_bsf_iterate(&opaque);
    while (bsf != nullptr)
    {
        list << bsf;
        bsf = av_bsf_iterate(&opaque);
    }
    return list;
}

bool HFFmpegUtil::fixNoPts(AVPacket *packet, AVStream *stream, int index)
{
    if (packet->pts != AV_NOPTS_VALUE)
        return false;

    auto time_base = av_q2d(stream->time_base);
    auto duration = 1.0 / av_q2d(stream->r_frame_rate);
    packet->pts = index * duration / time_base;
    packet->dts = packet->pts;
    packet->duration = duration / time_base;
    return true;
}

HE_CONTROL_END_NAMESPACE
