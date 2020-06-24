#pragma once

#include "HFFmpegThread.h"
#include "HFFmpeg.h"

HE_CONTROL_BEGIN_NAMESPACE

class HFFmpegThreadPrivate
{
public:
    HFFmpegThreadPrivate();

public:
    volatile bool stopped = false;                  // 线程停止标志位
    volatile bool play = false;                     // 播放视频标志位

    QString url;                                    // 视频流地址
    int videoWidth = 0;                             // 视频宽度
    int videoHeight = 0;                            // 视频高度
    int videoIndex = -1;                            // 视频流索引
    int audioIndex = -1;                            // 音频流索引

    AVDictionary *options = nullptr;                // 连接选项
    AVFormatContext *formatContext = nullptr;       // 格式
    AVCodecContext *videoCodecContext = nullptr;    // 视频解码器
    AVCodecContext *audioCodecContext = nullptr;    // 音频解码器
    SwsContext *swsContext = nullptr;               // 处理图片数据对象
    AVCodec *videoCodec = nullptr;                  // 视频解码
    AVCodec *audioCodec = nullptr;                  // 音频解码

    uint8_t *buffer = nullptr;                      // 存储解码后图片buffer
    AVPacket *packet = nullptr;                     // 包对象
    AVFrame *frame1 = nullptr;                      // 帧对象
    AVFrame *frame2 = nullptr;                      // 帧对象
};

HE_CONTROL_END_NAMESPACE

