/***************************************************************************************************
**      2020-06-12  HFFmpegUtil 工具类。
***************************************************************************************************/

#pragma once

#include "HControlGlobal.h"
#include <QtCore/QVariantMap>

extern "C" {
#include "libavutil/avutil.h"
#include "libavcodec/avcodec.h"
}

class AVFormatContext;
class AVFilterContext;
class AVStream;
class AVInputFormat;
class AVOutputFormat;
class AVFilter;

HE_CONTROL_BEGIN_NAMESPACE

class HE_CONTROL_EXPORT HFFmpegUtil
{
public:
    // 初始化
    static void initLib();
    // 创建格式上下文 - 输入
    static AVFormatContext *createFormatContext(QString url, QString formatName = QString(), AVDictionary *options = nullptr);
    // 创建格式上下文 - 输出
    static AVFormatContext *createFormatContext(QString url, AVCodecParameters *codecpars);
    static AVFormatContext *createFormatContext(QString url, QList<AVCodecParameters *> codecpars);
    // 创建编解码器上下文 - 输入
    static AVCodecContext *createCodecContext(AVFormatContext *context, AVMediaType type, AVDictionary *options, int *index);
    // 创建BSF上下文
    static AVBSFContext *createBSFContext(QString name, AVStream *stream);
    // 创建过滤器上下文
    static QList<AVFilterContext *> createFilterContext(AVCodecContext *codecContext, AVStream *stream, QString filters);
    // 创建流
    static AVStream *createStream(AVFormatContext *formatContext, AVCodecContext *codecContext);
    static AVStream *createStream(AVFormatContext *formatContext, AVCodecParameters *codecpar);
    // 创建帧
    static AVFrame *createFrame(AVPixelFormat format, int width, int height);
    static AVFrame *createFrame(AVSampleFormat format, int samples);
    // 解包
    static bool decodePacket(AVCodecContext *codecContext, AVPacket *packet, std::function<bool(AVFrame *)> handle);
    // 编包
    static bool encoderPacket(AVCodecContext *codecContext, AVFrame *frame, std::function<bool(AVPacket *)> handle);
    // 过滤
    static bool filter(QList<AVFilterContext *> filters, AVFrame *frame, std::function<bool(AVFrame *)> handle);
    // 显示所有信息
    static void showAllInfo();
    // 显示对象选项
    static void showObjectOpt(void *object);
    // 信息
    static QVariantMap getVersionInfo();
    // 协议
    static QStringList getProtocol(int output);
    // 输入封装格式
    static QList<const AVInputFormat *> getInputFormat();
    // 输出封装格式
    static QList<const AVOutputFormat *> getOutputFormat();
    // 编解码器
    static QList<const AVCodec *> getCodec(std::function<bool(const AVCodec *)> filter = nullptr);
    // 编码器
    static QList<const AVCodec *> getEncoder();
    // 编码器
    static AVCodec *getEncoder(AVCodecID id);
    // 解码器
    static QList<const AVCodec *> getDecoder();
    // 滤镜
    static QList<const AVFilter *> getFilter();
    // BSF
    static QList<const AVBitStreamFilter *> getBSF();
    // FIX：No PTS (Example: Raw H.264)
    static bool fixNoPts(AVPacket *packet, AVStream *stream, int index);
};

HE_CONTROL_END_NAMESPACE

