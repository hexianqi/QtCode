#include "HFFmpegThread_p.h"
#include "HFFmpegHelper.h"
#include <QtGui/QImage>
#include <QtCore/QtDebug>

HE_CONTROL_BEGIN_NAMESPACE

HFFmpegThreadPrivate::HFFmpegThreadPrivate()
{
    HFFmpegHelper::initLib();
}

HFFmpegThread::HFFmpegThread(QObject *parent) :
    QThread(parent),
    d_ptr(new HFFmpegThreadPrivate)
{
}

HFFmpegThread::HFFmpegThread(HFFmpegThreadPrivate &p, QObject *parent) :
    QThread(parent),
    d_ptr(&p)
{

}

void HFFmpegThread::run()
{
    while (!d_ptr->stopped)
    {
        if (d_ptr->play)
        {
            init();
            d_ptr->play = false;
            continue;
        }

        if (av_read_frame(d_ptr->formatContext, d_ptr->packet) >= 0)
        {
            // 判断当前包是视频还是音频
            int index = d_ptr->packet->stream_index;
            if (index == d_ptr->videoIndex)
            {
                // 解码视频流
                avcodec_send_packet(d_ptr->videoCodecContext, d_ptr->packet);
                while (avcodec_receive_frame(d_ptr->videoCodecContext, d_ptr->frame1) == 0)
                {
                    // 将数据转成一张图片
                    sws_scale(d_ptr->swsContext, (const uint8_t *const *)d_ptr->frame1->data,
                              d_ptr->frame1->linesize, 0, d_ptr->videoHeight,
                              d_ptr->frame2->data, d_ptr->frame2->linesize);

                    // 以下两种方法都可以
                    // QImage image(avFrame2->data[0], videoWidth, videoHeight, QImage::Format_RGB32);
                    QImage image((uchar *)d_ptr->buffer, d_ptr->videoWidth, d_ptr->videoHeight, QImage::Format_RGB32);
                    if (!image.isNull())
                        emit receiveImage(image);
                    msleep(1);
                }
            }
            else if (index == d_ptr->audioIndex)
            {
                // 解码音频流,这里暂不处理,以后交给sdl播放
            }
        }

        av_packet_unref(d_ptr->packet);
        av_freep(d_ptr->packet);
        msleep(1);
    }

    // 线程结束后释放资源
    free();
    d_ptr->stopped = false;
    d_ptr->play = false;
}

HFFmpegThread::~HFFmpegThread()
{

}

void HFFmpegThread::setUrl(const QString &value)
{
    d_ptr->url = value;
}

bool HFFmpegThread::init()
{
    int width, height;
    // 在打开码流前指定各种参数（探测时间、超时时间、最大延时等）
    // 设置缓存大小（1080p可将值调大）
    av_dict_set(&d_ptr->options, "buffer_size", "8192000", 0);
    // 设置打开方式（tcp或udp）
    av_dict_set(&d_ptr->options, "rtsp_transport", "tcp", 0);
    // 设置超时断开连接时间（单位微秒）
    av_dict_set(&d_ptr->options, "stimeout", "3000000", 0);
    // 设置最大时延（单位微秒）
    av_dict_set(&d_ptr->options, "max_delay", "1000000", 0);
    // 自动开启线程数
    av_dict_set(&d_ptr->options, "threads", "auto", 0);

    // 打开视频流
    d_ptr->formatContext = avformat_alloc_context();
    if (avformat_open_input(&d_ptr->formatContext, d_ptr->url.toStdString().data(), nullptr, &d_ptr->options) < 0)
    {
        qDebug() << "Couldn't open input stream:" << d_ptr->url;
        return false;
    }

    // 释放设置参数
    if (d_ptr->options != nullptr)
        av_dict_free(&d_ptr->options);

    // 获取流信息
    if (avformat_find_stream_info(d_ptr->formatContext, nullptr) < 0)
    {
        qDebug() << "Couldn't find stream information.";
        return false;
    }

    //----------视频流部分----------
    {
        d_ptr->videoIndex = av_find_best_stream(d_ptr->formatContext, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
        if (d_ptr->videoIndex < 0)
        {
            qDebug() << "Couldn't find a video stream.";
            return false;
        }

        d_ptr->videoCodecContext = avcodec_alloc_context3(nullptr);
        if (avcodec_parameters_to_context(d_ptr->videoCodecContext, d_ptr->formatContext->streams[d_ptr->videoIndex]->codecpar) != 0)
        {
            printf("Couldn't copy codec context.\n");
            return false;
        }

        // 获取视频流解码器，或者指定解码器
        d_ptr->videoCodec = avcodec_find_decoder(d_ptr->videoCodecContext->codec_id);
        // d_ptr->videoDecoder = avcodec_find_decoder_by_name("h264_qsv");
        if (d_ptr->videoCodec == nullptr)
        {
            qDebug() << "Couldn't find video decoder.";
            return false;
        }

        // 设置加速解码
        d_ptr->videoCodecContext->lowres = d_ptr->videoCodec->max_lowres;
        d_ptr->videoCodecContext->flags2 |= AV_CODEC_FLAG2_FAST;

        // 打开视频解码器
        if (avcodec_open2(d_ptr->videoCodecContext, d_ptr->videoCodec, nullptr) < 0)
        {
            qDebug() << "Couldn't open video codec.";
            return false;
        }

        // 获取分辨率大小
        width = d_ptr->videoCodecContext->width;
        height = d_ptr->videoCodecContext->height;

        // 如果没有获取到宽高则返回
        if (width * height == 0)
        {
            qDebug() << "Couldn't find width height.";
            return false;
        }

        qDebug() << tr("视频流信息 -> 索引: %1  解码: %2  格式: %3  时长: %4 秒  分辨率: %5*%6")
                        .arg(d_ptr->videoIndex)
                        .arg(d_ptr->videoCodec->name)
                        .arg(d_ptr->formatContext->iformat->name)
                        .arg(d_ptr->formatContext->duration / 1000000)
                        .arg(width)
                        .arg(height);
    }

    //----------音频流部分开始----------
    {
        // 循环查找音频流索引
        d_ptr->audioIndex = -1;
        for (uint i = 0; i < d_ptr->formatContext->nb_streams; i++)
        {
            if (d_ptr->formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO)
            {
                d_ptr->audioIndex = i;
                break;
            }
        }

        // 有些没有音频流，所以这里不用返回
        if (d_ptr->audioIndex == -1)
        {
            qDebug() << "Couldn't find a audio stream.";
        }
        else
        {
            d_ptr->audioCodecContext = avcodec_alloc_context3(nullptr);
            if (avcodec_parameters_to_context(d_ptr->audioCodecContext, d_ptr->formatContext->streams[d_ptr->audioIndex]->codecpar) != 0)
            {
                printf("Couldn't copy codec context.\n");
                return false;
            }

            // 获取视频流解码器，或者指定解码器
            d_ptr->audioCodec = avcodec_find_decoder(d_ptr->audioCodecContext->codec_id);
            // d_ptr->audioDecoder = avcodec_find_decoder_by_name("aac");
            if (d_ptr->audioCodec == nullptr)
            {
                qDebug() << "Couldn't find audio decoder.";
                return false;
            }

            // 打开音频解码器
            if (avcodec_open2(d_ptr->audioCodecContext, d_ptr->audioCodec, nullptr) < 0)
            {
                qDebug() <<  "Couldn't open audio codec.";
                return false;
            }
            qDebug() << tr("音频流信息 -> 索引: %1  解码: %2  比特率: %3  声道数: %4  采样: %5")
                            .arg(d_ptr->audioIndex)
                            .arg(d_ptr->audioCodec->name)
                            .arg(d_ptr->formatContext->bit_rate)
                            .arg(d_ptr->audioCodecContext->channels)
                            .arg(d_ptr->audioCodecContext->sample_rate);
        }
    }

    // 预分配好内存
    d_ptr->packet = av_packet_alloc();
    d_ptr->frame1 = av_frame_alloc();
    d_ptr->frame2 = av_frame_alloc();

    // 比较上一次文件的宽度高度,当改变时,需要重新分配内存
    if (d_ptr->videoWidth != width || d_ptr->videoHeight != height)
    {
        int byte = av_image_get_buffer_size(AV_PIX_FMT_RGB32, width, height, 1);
        d_ptr->buffer = (uint8_t *)av_malloc(byte * sizeof(uint8_t));
        d_ptr->videoWidth = width;
        d_ptr->videoHeight = height;
    }

    // 开辟缓存存储一帧数据
    av_image_fill_arrays(d_ptr->frame2->data, d_ptr->frame2->linesize, d_ptr->buffer, AV_PIX_FMT_RGB32, width, height, 1);
    // 图像转换
    d_ptr->swsContext = sws_getContext(width, height, d_ptr->videoCodecContext->pix_fmt,
                                       width, height, AV_PIX_FMT_RGB32,
                                       SWS_FAST_BILINEAR, nullptr, nullptr, nullptr);
    return true;
}

void HFFmpegThread::free()
{
    if (d_ptr->swsContext != nullptr)
    {
        sws_freeContext(d_ptr->swsContext);
        d_ptr->swsContext = nullptr;
    }
    if (d_ptr->packet != nullptr)
    {
        av_packet_unref(d_ptr->packet);
        d_ptr->packet = nullptr;
    }
    if (d_ptr->frame1 != nullptr)
    {
        av_frame_free(&d_ptr->frame1);
        d_ptr->frame1 = nullptr;
    }
    if (d_ptr->frame2 != nullptr)
    {
        av_frame_free(&d_ptr->frame2);
        d_ptr->frame2 = nullptr;
    }
    if (d_ptr->videoCodecContext != nullptr)
    {
        avcodec_close(d_ptr->videoCodecContext);
        d_ptr->videoCodecContext = nullptr;
    }
    if (d_ptr->audioCodecContext != nullptr)
    {
        avcodec_close(d_ptr->audioCodecContext);
        d_ptr->audioCodecContext = nullptr;
    }
    if (d_ptr->formatContext != nullptr)
    {
        avformat_close_input(&d_ptr->formatContext);
        d_ptr->formatContext = nullptr;
    }
    av_dict_free(&d_ptr->options);
}

void HFFmpegThread::play()
{
    d_ptr->play = true;
}

void HFFmpegThread::pause()
{

}

void HFFmpegThread::next()
{

}

void HFFmpegThread::stop()
{
    d_ptr->stopped = true;
    quit();
    wait(500);
}

HE_CONTROL_END_NAMESPACE
