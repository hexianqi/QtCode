#include "HFFmpegHelper.h"
#include "HFFmpeg.h"
#include <QtCore/QMutex>
#include <QtCore/QtDebug>

HE_CONTROL_BEGIN_NAMESPACE

bool __initialized = false;
bool __debug = true;
QMutex __mutex;

void HFFmpegHelper::initLib()
{
    if (__initialized)
        return;

    QMutexLocker locker(&__mutex);
    // 注册所有设备，主要用于本地摄像机播放支持
#ifdef ffmpegdevice
    avdevice_register_all();
#endif
    // 初始化网络流格式，使用网络流时必须先执行
    avformat_network_init();

    if (__debug)
    {
        qDebug() << "FFmpeg init ffmpeg lib ok.";
        qDebug() << "=== Info ===";
        auto info = getInfo();
        for (auto i = info.constBegin(); i != info.constEnd(); i++)
            qDebug() << i.key() << ":" << i.value().toString();
        qDebug() << "=== input protocols ===";
        for (auto p : getProtocol(0))
            qDebug() << p;
        qDebug() << "=== output protocols ===";
        for (auto p : getProtocol(1))
            qDebug() << p;
        qDebug() << "=== demuxer ===";
        for (auto p : getDemuxer())
            qDebug() << p->name;
        qDebug() << "=== muxer ===";
        for (auto p : getMuxer())
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
}

QVariantMap HFFmpegHelper::getInfo()
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

QStringList HFFmpegHelper::getProtocol(int output)
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

QList<const AVInputFormat *> HFFmpegHelper::getDemuxer()
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

QList<const AVOutputFormat *> HFFmpegHelper::getMuxer()
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

QList<const AVCodec *> HFFmpegHelper::getEncoder()
{
    QList<const AVCodec *> list;
    void *opaque = nullptr;
    auto *codec = av_codec_iterate(&opaque);
    while (codec != nullptr)
    {
        if(av_codec_is_encoder(codec))
            list << codec;
        codec = av_codec_iterate(&opaque);
    }
    return list;
}

QList<const AVCodec *> HFFmpegHelper::getDecoder()
{
    QList<const AVCodec *> list;
    void *opaque = nullptr;
    auto *codec = av_codec_iterate(&opaque);
    while (codec != nullptr)
    {
        if(av_codec_is_decoder(codec))
            list << codec;
        codec = av_codec_iterate(&opaque);
    }
    return list;
}

QList<const AVFilter *> HFFmpegHelper::getFilter()
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

QList<const AVBitStreamFilter *> HFFmpegHelper::getBSF()
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

HE_CONTROL_END_NAMESPACE
