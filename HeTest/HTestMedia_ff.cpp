//#include "HTestMedia.h"
//#include "HeControl/HFFmpegUtil.h"
//#include <QtCore/QFile>
//#include <QtCore/QDataStream>
//#include <QtCore/QDebug>

//HE_USE_NAMESPACE

//extern "C"
//{
//#include "libavcodec/avcodec.h"
//#include "libavdevice/avdevice.h"
//#include "libavformat/avformat.h"
//#include "libavutil/imgutils.h"
//#include "libavutil/opt.h"
//#include "libavutil/time.h"
//#include "libswscale/swscale.h"
//#include "libswresample/swresample.h"
//#include "libavfilter/buffersink.h"
//#include "libavfilter/buffersrc.h"
//#include "SDL2/SDL.h"
//};

//#define SFM_REFRESH_EVENT       (SDL_USEREVENT + 1)
//#define SFM_BREAK_EVENT         (SDL_USEREVENT + 2)
//#define MAX_AUDIO_FRAME_SIZE    192000                  // 1 second of 48khz 32bit audio

//void exportFile(AVPixelFormat format, FILE *file, uint8_t *data[], int size)
//{
//    if (file == nullptr)
//        return;

//    switch(format)
//    {
//    case AV_PIX_FMT_GRAY8:
//        fwrite(data[0], 1, size, file);
//        break;
//    case AV_PIX_FMT_YUV420P:
//        fwrite(data[0], 1, size, file);
//        fwrite(data[1], 1, size / 4, file);
//        fwrite(data[2], 1, size / 4, file);
//        break;
//    case AV_PIX_FMT_YUV422P:
//        fwrite(data[0], 1, size, file);
//        fwrite(data[1], 1, size / 2,file);
//        fwrite(data[2], 1, size / 2,file);
//        break;
//    case AV_PIX_FMT_YUV444P:
//        fwrite(data[0], 1, size, file);
//        fwrite(data[1], 1, size, file);
//        fwrite(data[2], 1, size, file);
//        break;
//    case AV_PIX_FMT_YUYV422:
//        fwrite(data[0], 1, size * 2, file);
//        break;
//    case AV_PIX_FMT_RGB24:
//        fwrite(data[0], 1, size * 3, file);
//        break;
//    default:
//        qDebug() << "Not Support Output Pixel Format.";
//        break;
//    }
//}

//void updateSDL(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect rect, uint8_t *data[], int linesize[])
//{
//    SDL_UpdateYUVTexture(texture, nullptr, data[0], linesize[0], data[1], linesize[1], data[2], linesize[2]);
//    SDL_RenderClear(renderer);
//    SDL_RenderCopy(renderer, texture, nullptr, &rect);
//    SDL_RenderPresent(renderer);
//}

//bool __threadExit = false;
//bool __threadPause = false;

//int sfpRefreshThread(void */*opaque*/)
//{
//    __threadExit = false;
//    __threadPause = false;

//    while (!__threadExit)
//    {
//        if(!__threadPause)
//        {
//            // Refresh
//            SDL_Event event;
//            event.type = SFM_REFRESH_EVENT;
//            SDL_PushEvent(&event);
//        }
//        SDL_Delay(40);
//    }
//    __threadExit = false;
//    __threadPause = false;
//    // Break
//    SDL_Event event;
//    event.type = SFM_BREAK_EVENT;
//    SDL_PushEvent(&event);
//    return 0;
//}

//bool displaySDL(AVFormatContext *formatContext, AVCodecContext *codecContext, int index, QString title)
//{
//    auto width = codecContext->width;
//    auto height = codecContext->height;
//    auto packet = av_packet_alloc();
//    auto frameYUV = av_frame_alloc();
//    auto buffer = (unsigned char *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_YUV420P,  width, height, 1));
//    av_image_fill_arrays(frameYUV->data, frameYUV->linesize, buffer, AV_PIX_FMT_YUV420P, width, height, 1);
//    auto swsContext = sws_getContext(width, height, codecContext->pix_fmt,
//                                     width, height, AV_PIX_FMT_YUV420P,
//                                     SWS_BICUBIC, nullptr, nullptr, nullptr);
//    //------------SDL----------------
//    SDL_Event event;
//    SDL_Rect rect = { 0, 0, width, height };
//    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
//    {
//        qDebug() << QString( "Couldn't initialize SDL - %1.").arg(SDL_GetError());
//        return false;
//    }
//    auto window = SDL_CreateWindow(title.toStdString().data(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
//    if (!window)
//    {
//        qDebug() << QString( "Couldn't create window - exiting: - %1.").arg(SDL_GetError());
//        return false;
//    }
//    auto renderer = SDL_CreateRenderer(window, -1, 0);
//    auto texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, width, height);
//    auto handle = [=](AVFrame *frame)
//    {
//        sws_scale(swsContext, (const unsigned char* const*)frame->data, frame->linesize, 0, height, frameYUV->data, frameYUV->linesize);
//        updateSDL(texture, renderer, rect, frameYUV->data, frameYUV->linesize);
//        return true;
//    };
//    SDL_CreateThread(sfpRefreshThread, nullptr, nullptr);
//    //------------Event Loop----------------
//    while (1)
//    {
//        SDL_WaitEvent(&event);
//        if (event.type == SFM_REFRESH_EVENT)
//        {
//            while (1)
//            {
//                if (av_read_frame(formatContext, packet) < 0)
//                    __threadExit = true;
//                if (packet->stream_index == index)
//                    break;
//            }
//            if (!HFFmpegUtil::decodePacket(codecContext, packet, handle))
//                break;
//            av_packet_unref(packet);
//        }
//        else if (event.type == SDL_KEYDOWN)
//        {
//            if (event.key.keysym.sym == SDLK_SPACE)
//                __threadPause = !__threadPause;
//        }
//        else if (event.type==SDL_QUIT)
//        {
//            __threadExit = true;
//        }
//        else if (event.type == SFM_BREAK_EVENT)
//        {
//            break;
//        }
//    }

//    //------------Free----------------
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//    sws_freeContext(swsContext);
//    av_frame_free(&frameYUV);
//    return true;
//}

////Buffer:
////|-----------|-------------|
////chunk-------pos---len-----|
//static Uint8 *__audioChunk;
//static Uint8 *__audioPos;
//static int __audioLen;

//// The audio function callback takes the following parameters:
//// stream: A pointer to the audio buffer to be filled
//// len: The length (in bytes) of the audio buffer
//void fillAudio(void */*userdata*/, Uint8 *stream, int len)
//{
//    SDL_memset(stream, 0, len);
//    if (__audioLen == 0)
//        return;

//    if (len > __audioLen)
//        len = __audioLen;

//    SDL_MixAudio(stream, __audioPos, len, SDL_MIX_MAXVOLUME);
//    __audioPos += len;
//    __audioLen -= len;
//}

//bool HTestMedia::videoPlayer(QString fileName, bool output)
//{
//    if (fileName.isEmpty())
//        fileName = "media\\Titanic.ts";

//    //------------FFmpeg----------------
//    avformat_network_init();
//    auto formatContext = HFFmpegUtil::createFormatContext(fileName);
//    if (formatContext == nullptr)
//        return false;
//    auto index = -1;
//    auto codecContext = HFFmpegUtil::createCodecContext(formatContext, AVMEDIA_TYPE_VIDEO, nullptr, &index);
//    if (codecContext == nullptr)
//        return false;
//    av_dump_format(formatContext, 0, fileName.toStdString().data(), 0);

//    auto packet = av_packet_alloc();
//    auto frameYUV = av_frame_alloc();
//    auto width = codecContext->width;
//    auto height = codecContext->height;
//    auto ysize = codecContext->width * codecContext->height;
//    auto buffer = (unsigned char *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_YUV420P,  width, height, 1));
//    av_image_fill_arrays(frameYUV->data, frameYUV->linesize, buffer, AV_PIX_FMT_YUV420P, width, height, 1);
//    auto swsContext = sws_getContext(width, height, codecContext->pix_fmt,
//                                     width, height, AV_PIX_FMT_YUV420P,
//                                     SWS_BICUBIC, nullptr, nullptr, nullptr);

//    //------------Output----------------
//    FILE *file = nullptr;
//    if (output)
//        file = fopen("output.yuv","wb+");

//    //------------SDL----------------
//    SDL_Rect rect;
//    rect.x = 0;
//    rect.y = 0;
//    rect.w = width;
//    rect.h = height;
//    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
//    {
//        qDebug() << QString( "Couldn't initialize SDL - %1.").arg(SDL_GetError());
//        return false;
//    }
//    auto window = SDL_CreateWindow("Simplest ffmpeg player's Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
//    if (!window)
//    {
//        qDebug() << QString( "Couldn't create window - exiting: %1.").arg(SDL_GetError());
//        return false;
//    }
//    auto renderer = SDL_CreateRenderer(window, -1, 0);
//    auto texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, width, height);



//    //------------PLAY----------------
//    auto handle = [=](AVFrame *frame)
//    {
//        sws_scale(swsContext, (const unsigned char* const*)frame->data, frame->linesize, 0, height, frameYUV->data, frameYUV->linesize);
//        exportFile(AV_PIX_FMT_YUV420P, file, frameYUV->data, ysize);
//        updateSDL(texture, renderer, rect, frameYUV->data, frameYUV->linesize);
//        SDL_Delay(40);
//        return true;
//    };
//    while (av_read_frame(formatContext, packet) >= 0)
//    {
//        if (packet->stream_index == index)
//        {
//            if (!HFFmpegUtil::decodePacket(codecContext, packet, handle))
//                return false;
//        }
//        av_packet_unref(packet);
//    }
//    // flush cached frames
//    while (1)
//    {
//        if (!HFFmpegUtil::decodePacket(codecContext, packet, handle))
//            break;
//    }

//    //------------Free----------------
//    if (file != nullptr)
//        fclose(file);
//    sws_freeContext(swsContext);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//    av_frame_free(&frameYUV);
//    avcodec_close(codecContext);
//    avformat_close_input(&formatContext);
//    return true;
//}

//bool HTestMedia::videoPlayer_SU(QString fileName)
//{
//    if (fileName.isEmpty())
//        fileName = "media\\Titanic.ts";

//    //------------FFmpeg----------------
//    avformat_network_init();
//    auto formatContext = HFFmpegUtil::createFormatContext(fileName);
//    if (formatContext == nullptr)
//        return false;
//    auto index = -1;
//    auto codecContext = HFFmpegUtil::createCodecContext(formatContext, AVMEDIA_TYPE_VIDEO, nullptr, &index);
//    if (codecContext == nullptr)
//        return false;
//    av_dump_format(formatContext,0, fileName.toStdString().data(), 0);

//    if (displaySDL(formatContext, codecContext, index, "Simplest ffmpeg player's Window"))
//        return false;

//    avcodec_close(codecContext);
//    avformat_close_input(&formatContext);
//    return true;
//}

//bool HTestMedia::audioPlayer(QString fileName, bool output)
//{
//    if (fileName.isEmpty())
//        fileName = "media\\xiaoqingge.mp3";

//    //------------FFmpeg----------------
//    avformat_network_init();
//    auto formatContext = HFFmpegUtil::createFormatContext(fileName);
//    if (formatContext == nullptr)
//        return false;
//    int index;
//    auto codecContext = HFFmpegUtil::createCodecContext(formatContext, AVMEDIA_TYPE_AUDIO, nullptr, &index);
//    if (codecContext == nullptr)
//        return false;
//    av_dump_format(formatContext, 0, fileName.toStdString().data(), 0);

//    auto packet = av_packet_alloc();
//    int sampleRate = 44100;
//    uint64_t channelLayout = AV_CH_LAYOUT_STEREO;
//    AVSampleFormat sampleFmt = AV_SAMPLE_FMT_S16;
//    auto channels = av_get_channel_layout_nb_channels(channelLayout);
//    auto samples = codecContext->frame_size;    // nb_samples: AAC-1024 MP3-1152
//    auto bufferSize = av_samples_get_buffer_size(nullptr, channels, samples, sampleFmt, 1);
//    auto buffer = (unsigned char *)av_malloc(MAX_AUDIO_FRAME_SIZE * 2);
//    // FIX:Some Codec's Context Information is missing
//    auto inChannelLayout = av_get_default_channel_layout(codecContext->channels);
//    auto swrContext = swr_alloc_set_opts(nullptr,
//                                         channelLayout, sampleFmt, sampleRate,
//                                         inChannelLayout, codecContext->sample_fmt, codecContext->sample_rate,
//                                         0, nullptr);
//    swr_init(swrContext);

//    //------------Output----------------
//    FILE *file = nullptr;
//    if (output)
//        file = fopen("output.pcm","wb+");

//    //------------SDL----------------
//    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
//    {
//        qDebug() << QString( "Couldn't initialize SDL - %1.").arg(SDL_GetError());
//        return false;
//    }

//    SDL_AudioSpec spec;
//    spec.freq = sampleRate;
//    spec.format = AUDIO_S16SYS;
//    spec.channels = channels;
//    spec.silence = 0;
//    spec.samples = samples;
//    spec.callback = fillAudio;
//    spec.userdata = codecContext;
//    if (SDL_OpenAudio(&spec, nullptr) < 0)
//    {
//        qDebug() << QString( "Couldn't open audio: %1.").arg(SDL_GetError());
//        return false;
//    }

//    //------------PLAY----------------
//    int frameIndex = 0;
//    SDL_PauseAudio(0);
//    auto handle = [&](AVFrame *frame)
//    {
//        swr_convert(swrContext, &buffer, MAX_AUDIO_FRAME_SIZE, (const uint8_t **)frame->data , frame->nb_samples);
//        if (file != nullptr)
//            fwrite(buffer, 1, bufferSize, file);
//        qDebug() << QString("index:%1    pts:%2    packet size:%3").arg(frameIndex++, 5).arg(packet->pts, 11).arg(packet->size);
//        return true;
//    };
//    while (av_read_frame(formatContext, packet) >= 0)
//    {
//        if (packet->stream_index == index)
//        {
//            if (!HFFmpegUtil::decodePacket(codecContext, packet, handle))
//                return false;

//            while(__audioLen > 0) // Wait until finish
//                SDL_Delay(1);
//            // Set audio buffer (PCM data) buffer length
//            __audioChunk = (Uint8 *)buffer;
//            __audioLen = bufferSize;
//            __audioPos = __audioChunk;
//        }
//        av_packet_unref(packet);
//    }

//    //------------Free----------------
//    swr_free(&swrContext);
//    SDL_CloseAudio();
//    SDL_Quit();
//    if (file != nullptr)
//        fclose(file);
//    av_free(buffer);
//    avcodec_close(codecContext);
//    avformat_close_input(&formatContext);
//    return true;
//}

//bool HTestMedia::yuv2jpg(QString iFileName, QString oFileName)
//{
//    if (iFileName.isEmpty())
//        iFileName = "media\\cuc_view_480x272.yuv";
//    if (oFileName.isEmpty())
//        oFileName = "output.jpg";

//    //------------FFmpeg----------------
//    auto formatContext = HFFmpegUtil::createFormatContext(oFileName, nullptr);
//    if (formatContext == nullptr)
//        return false;

//    auto codecId = formatContext->oformat->video_codec;
//    auto encoder = HFFmpegUtil::getEncoder(codecId);
//    if (encoder == nullptr)
//        return false;

//    auto codecContext = avcodec_alloc_context3(encoder);
//    codecContext->codec_id = codecId;
//    codecContext->codec_type = AVMEDIA_TYPE_VIDEO;
//    codecContext->pix_fmt = encoder->pix_fmts[0];
//    codecContext->width = 480;
//    codecContext->height = 272;
//    codecContext->time_base.num = 1;
//    codecContext->time_base.den = 25;
//    if (avcodec_open2(codecContext, encoder, nullptr) < 0)
//    {
//        qDebug() << "Couldn't open encoder.";
//        return false;
//    }

//    auto stream = HFFmpegUtil::createStream(formatContext, codecContext);
//    if (stream == nullptr)
//        return false;

//    av_dump_format(formatContext, 0, oFileName.toStdString().data(), 1);

//    auto frame = HFFmpegUtil::createFrame(codecContext->pix_fmt, codecContext->width, codecContext->height);
//    auto ysize = codecContext->width * codecContext->height;
//    auto buffer = (unsigned char *)av_malloc(av_image_get_buffer_size(codecContext->pix_fmt, codecContext->width, codecContext->height, 1));
//    av_image_fill_arrays(frame->data, frame->linesize, buffer, codecContext->pix_fmt, codecContext->width, codecContext->height, 1);

//    // Write Header
//    if (avformat_write_header(formatContext, nullptr) < 0)
//    {
//        qDebug() << "Write Header Error.";
//    }
//    // Read YUV
//    auto file = fopen(iFileName.toStdString().data(), "rb");
//    auto handle = [&](AVPacket *packet)
//    {
//        packet->stream_index = stream->index;
//        return av_write_frame(formatContext, packet) >= 0;
//    };
//    if (fread(buffer, 1, ysize * 3 / 2, file) <=0)
//    {
//        qDebug() << "Could not read input file.";
//        return false;
//    }
//    frame->data[0] = buffer;                   // Y
//    frame->data[1] = buffer + ysize;           // U
//    frame->data[2] = buffer + ysize * 5 / 4;   // V
//    frame->pts = 0;
//    // Encode
//    if (!HFFmpegUtil::encoderPacket(codecContext, frame, handle))
//    {
//        qDebug() << "Encode Failed! ";
//        return false;
//    }
//    // Write Trailer
//    av_write_trailer(formatContext);
//    printf("Encode Successful.\n");

//    //------------Free----------------
//    fclose(file);
//    avcodec_close(codecContext);
//    av_free(frame);
//    av_free(buffer);
//    avio_close(formatContext->pb);
//    avformat_free_context(formatContext);
//    return true;
//}

//bool HTestMedia::videoEncoder(QString iFileName, QString oFileName)
//{
//    if (iFileName.isEmpty())
//        iFileName = "media\\ds_480x272.yuv";
//    if (oFileName.isEmpty())
//        oFileName = "output.h264";

//    auto frameNum = 100;
//    auto formatContext = HFFmpegUtil::createFormatContext(oFileName, nullptr);
//    if (formatContext == nullptr)
//        return false;

//    auto codecId = formatContext->oformat->video_codec;
//    auto encoder = HFFmpegUtil::getEncoder(codecId);
//    if (encoder == nullptr)
//        return false;

//    auto codecContext = avcodec_alloc_context3(encoder);
//    codecContext->codec_id = codecId;
//    codecContext->codec_type = AVMEDIA_TYPE_VIDEO;
//    codecContext->pix_fmt = encoder->pix_fmts[0];
//    codecContext->width = 480;
//    codecContext->height = 272;
//    codecContext->bit_rate = 400000;
//    codecContext->gop_size = 250;
//    codecContext->time_base.num = 1;
//    codecContext->time_base.den = 25;
//    codecContext->qmin = 10;
//    codecContext->qmax = 51;
//    codecContext->max_b_frames = 3;
//    // Set Option
//    AVDictionary *options = nullptr;
//    if (codecId == AV_CODEC_ID_H264)
//    {
//        av_dict_set(&options, "preset", "slow", 0);
//        av_dict_set(&options, "tune", "zerolatency", 0);
//    }
//    if (codecId == AV_CODEC_ID_H265)
//    {
//        av_dict_set(&options, "preset", "ultrafast", 0);
//        av_dict_set(&options, "tune", "zero-latency", 0);
//    }
//    if (avcodec_open2(codecContext, encoder, &options) < 0)
//    {
//        qDebug() << "Couldn't open encoder.";
//        return false;
//    }

//    auto stream = HFFmpegUtil::createStream(formatContext, codecContext);
//    if (stream == nullptr)
//        return false;

//    av_dump_format(formatContext, 0, oFileName.toStdString().data(), 1);

//    auto frame = HFFmpegUtil::createFrame(codecContext->pix_fmt, codecContext->width, codecContext->height);
//    auto ysize = codecContext->width * codecContext->height;
//    auto size = av_image_get_buffer_size(codecContext->pix_fmt, codecContext->width, codecContext->height, 1);
//    auto buffer = (unsigned char *)av_malloc(size);
//    av_image_fill_arrays(frame->data, frame->linesize, buffer, codecContext->pix_fmt, codecContext->width, codecContext->height, 1);

//    // Write Header
//    if (avformat_write_header(formatContext, nullptr) < 0)
//    {
//        qDebug() << "Write Header Error.";
//    }
//    // Write Content
//    auto frameIndex = 0;
//    auto file = fopen(iFileName.toStdString().data(), "rb");
//    auto handle = [&](AVPacket *packet)
//    {
//        qDebug() << QString("Succeed to encode frame:%1      size:%2").arg(frameIndex++, 4).arg(packet->size, 5);
//        packet->stream_index = stream->index;
//        return av_write_frame(formatContext, packet) >= 0;
//    };
//    for (int i = 0; i < frameNum; i++)
//    {
//        // Read YUV data
//        if (fread(buffer, 1, ysize * 3 / 2, file) <= 0)
//        {
//            qDebug() << "Failed to read raw data! ";
//            return false;
//        }
//        else if (feof(file))
//        {
//            break;
//        }
//        frame->data[0] = buffer;                    // Y
//        frame->data[1] = buffer + ysize;            // U
//        frame->data[2] = buffer + ysize * 5 / 4;    // V
//        frame->pts = i * stream->time_base.den / (stream->time_base.num * 25);
//        // Encode
//        HFFmpegUtil::encoderPacket(codecContext, frame, handle);
//    }
//    // Flush Encoder
//    HFFmpegUtil::encoderPacket(codecContext, nullptr, handle);
//    // Write Trailer
//    av_write_trailer(formatContext);
//    qDebug() << "Encode Successful.";
//    //------------Free----------------
//    fclose(file);
//    avcodec_close(codecContext);
//    av_free(frame);
//    av_free(buffer);
//    avio_close(formatContext->pb);
//    avformat_free_context(formatContext);
//    return true;
//}

//bool HTestMedia::audioEncoder(QString iFileName, QString oFileName)
//{
//    if (iFileName.isEmpty())
//        iFileName = "media\\tdjm.pcm";
//    if (oFileName.isEmpty())
//        oFileName = "output.mp3";

//    auto frameNum = 1000;
//    auto formatContext = HFFmpegUtil::createFormatContext(oFileName, nullptr);
//    if (formatContext == nullptr)
//        return false;

//    auto codecId = formatContext->oformat->audio_codec;
//    auto encoder = HFFmpegUtil::getEncoder(codecId);
//    if (encoder == nullptr)
//        return false;

//    auto codecContext = avcodec_alloc_context3(encoder);
//    codecContext->codec_id = codecId;
//    codecContext->codec_type = AVMEDIA_TYPE_AUDIO;
//    codecContext->sample_fmt = encoder->sample_fmts[0];
//    codecContext->sample_rate = 44100;
//    codecContext->channel_layout = AV_CH_LAYOUT_STEREO;
//    codecContext->channels = av_get_channel_layout_nb_channels(AV_CH_LAYOUT_STEREO);
//    codecContext->bit_rate = 64000;
//    codecContext->profile = FF_PROFILE_AAC_MAIN;
//    codecContext->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;
//    if (avcodec_open2(codecContext, encoder, nullptr) < 0)
//    {
//        qDebug() << "Couldn't open encoder.";
//        return false;
//    }

//    auto stream = HFFmpegUtil::createStream(formatContext, codecContext);
//    if (stream == nullptr)
//        return false;

//    av_dump_format(formatContext, 0, oFileName.toStdString().data(), 1);

//    auto frame = HFFmpegUtil::createFrame(codecContext->sample_fmt, codecContext->frame_size);
//    auto size = av_samples_get_buffer_size(nullptr, codecContext->channels, codecContext->frame_size, codecContext->sample_fmt, 1);
//    auto buffer = (unsigned char *)av_malloc(size);
//    avcodec_fill_audio_frame(frame, codecContext->channels, codecContext->sample_fmt,(const uint8_t*)buffer, size, 1);
//    auto swrContext = swr_alloc_set_opts(nullptr,
//                                         codecContext->channel_layout, codecContext->sample_fmt, codecContext->sample_rate,
//                                         AV_CH_LAYOUT_STEREO, AV_SAMPLE_FMT_S16,  44100,
//                                         0, nullptr);
//    swr_init(swrContext);

//    // Write Header
//    if (avformat_write_header(formatContext, nullptr) < 0)
//    {
//        qDebug() << "Write Header Error.";
//    }
//    // Write Content
//    uint8_t *outs[2];
//    int len = 4096;
//    outs[0] = (uint8_t *)malloc(len);
//    outs[1] = (uint8_t *)malloc(len);
//    auto frameIndex = 0;
//    auto file = fopen(iFileName.toStdString().data(), "rb");
//    auto handle = [&](AVPacket *packet)
//    {
//        qDebug() << QString("Succeed to encode frame:%1      size:%2").arg(frameIndex++, 4).arg(packet->size, 5);
//        packet->stream_index = stream->index;
//        return av_write_frame(formatContext, packet) >= 0;
//    };

//    for (int i = 0; i < frameNum; i++)
//    {
//        // Read PCM
//        if (fread(buffer, 1, size, file) <= 0)
//        {
//            qDebug() << "Failed to read raw data! ";
//            return false;
//        }
//        else if(feof(file))
//        {
//            break;
//        }
//        swr_convert(swrContext, outs, len * 4, (const uint8_t **)&buffer, len / 4);
//        frame->data[0] =(uint8_t*)outs[0];
//        frame->data[1] =(uint8_t*)outs[1];
//        frame->pts = i * 100;
//        // Encode
//        HFFmpegUtil::encoderPacket(codecContext, frame, handle);
//    }
//    // Flush Encoder
//    HFFmpegUtil::encoderPacket(codecContext, nullptr, handle);
//    // Write Trailer
//    av_write_trailer(formatContext);
//    qDebug() << "Encode Successful.";
//    //------------Free----------------
//    fclose(file);
//    avcodec_close(codecContext);
//    av_free(frame);
//    av_free(buffer);
//    avio_close(formatContext->pb);
//    avformat_free_context(formatContext);
//    return true;
//}

//bool HTestMedia::remuxer(QString iFileName, QString oFileName)
//{
//    if (iFileName.isEmpty())
//        iFileName = "media\\cuc_ieschool1.flv";
//    if (oFileName.isEmpty())
//        oFileName = "output.mp4";

//    // Input
//    auto iFormatContext = HFFmpegUtil::createFormatContext(iFileName);
//    if (iFormatContext == nullptr)
//        return false;
//    av_dump_format(iFormatContext, 0, iFileName.toStdString().data(), 0);

//    // Output
//    QList<AVCodecParameters *> codecpars;
//    for (uint i = 0; i < iFormatContext->nb_streams; i++)
//        codecpars << iFormatContext->streams[i]->codecpar;
//    auto oFormatContext = HFFmpegUtil::createFormatContext(oFileName, codecpars);
//    if (oFormatContext == nullptr)
//        return false;
//    av_dump_format(oFormatContext, 0, oFileName.toStdString().data(), 1);

//    // Write file header
//    if (avformat_write_header(oFormatContext, nullptr) < 0)
//    {
//        qDebug() << "Write Header Error.";
//        return false;
//    }
//    // Write Content
//    auto frameIndex = 0;
//    auto packet = av_packet_alloc();
//    while (av_read_frame(iFormatContext, packet) >= 0)
//    {
//        qDebug() << QString("Write %1 frames to output file.").arg(frameIndex++, 8);
//        auto iStream  = iFormatContext->streams[packet->stream_index];
//        auto oStream = oFormatContext->streams[packet->stream_index];
//        packet->pts = av_rescale_q_rnd(packet->pts, iStream->time_base, oStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
//        packet->dts = av_rescale_q_rnd(packet->dts, iStream->time_base, oStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
//        packet->duration = av_rescale_q(packet->duration, iStream->time_base, oStream->time_base);
//        packet->pos = -1;
//        if (av_interleaved_write_frame(oFormatContext, packet) < 0)
//        {
//            qDebug() << "Error muxing packet.";
//            return false;
//        }
//        av_packet_unref(packet);
//    }
//    // Write Trailer
//    av_write_trailer(oFormatContext);
//    qDebug() << "Muxing Successful.";
//    //------------Free----------------
//    avformat_close_input(&iFormatContext);
//    if (oFormatContext && !(oFormatContext->oformat->flags & AVFMT_NOFILE))
//        avio_close(oFormatContext->pb);
//    avformat_free_context(oFormatContext);
//    return true;
//}

//bool HTestMedia::demuxer(QString iFileName, QString oFileNameV, QString oFileNameA)
//{
//    if (iFileName.isEmpty())
//        iFileName = "media\\cuc_ieschool.flv";
//    if (oFileNameV.isEmpty())
//        oFileNameV = "output.h264";
//    if (oFileNameA.isEmpty())
//        oFileNameA = "output.aac";

//    // Input
//    auto iFormatContext = HFFmpegUtil::createFormatContext(iFileName);
//    if (iFormatContext == nullptr)
//        return false;
//    auto videoIndex = av_find_best_stream(iFormatContext, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
//    if (videoIndex < 0)
//    {
//        qDebug() << QString("Couldn't find %1 stream.").arg(av_get_media_type_string(AVMEDIA_TYPE_VIDEO));
//        return false;
//    }
//    auto audioIndex = av_find_best_stream(iFormatContext, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);
//    if (audioIndex < 0)
//    {
//        qDebug() << QString("Couldn't find %1 stream.").arg(av_get_media_type_string(AVMEDIA_TYPE_AUDIO));
//        return false;
//    }
//    av_dump_format(iFormatContext, 0, iFileName.toStdString().data(), 0);
//    // Output video
//    auto oFormatContextV = HFFmpegUtil::createFormatContext(oFileNameV, iFormatContext->streams[videoIndex]->codecpar);
//    if (oFormatContextV == nullptr)
//        return false;
//    av_dump_format(oFormatContextV, 0, oFileNameV.toStdString().data(), 1);
//    // Output audio
//    auto oFormatContextA = HFFmpegUtil::createFormatContext(oFileNameA, iFormatContext->streams[videoIndex]->codecpar);
//    if (oFormatContextA == nullptr)
//        return false;
//    av_dump_format(oFormatContextV, 0, oFileNameA.toStdString().data(), 1);

//    // Write Header
//    if (avformat_write_header(oFormatContextV, nullptr) < 0)
//    {
//        qDebug() << "Error occurred when opening video output file.";
//        return false;
//    }
//    if (avformat_write_header(oFormatContextA, nullptr) < 0)
//    {
//        qDebug() << "Error occurred when opening audio output file.";
//        return false;
//    }
//    // Write Content
////    auto h264bsfc = av_bitstream_filter_init("h264_mp4toannexb");
//    auto packet = av_packet_alloc();
//    while (av_read_frame(iFormatContext, packet) >= 0)
//    {
//        AVFormatContext *oFormatContext = nullptr;
//        AVStream *oStream = nullptr;
//        auto iStream = iFormatContext->streams[packet->stream_index];
//        if(packet->stream_index == videoIndex)
//        {
//            oStream = oFormatContextV->streams[0];
//            oFormatContext = oFormatContextV;
//            qDebug() << QString("Write Video Packet. size:%1    pts:%2.").arg(packet->size, 5).arg(packet->pts, 11);
////            av_bitstream_filter_filter(h264bsfc, inStream->codec, nullptr, &packet->data, &packet->size, packet->data, packet->size, 0);
//        }
//        else if(packet->stream_index == audioIndex)
//        {
//            oStream = oFormatContextA->streams[0];
//            oFormatContext = oFormatContextA;
//            qDebug() << QString("Write Audio Packet. size:%1    pts:%2.").arg(packet->size, 5).arg(packet->pts, 11);
//        }
//        else
//        {
//            continue;
//        }

//        packet->pts = av_rescale_q_rnd(packet->pts, iStream->time_base, oStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
//        packet->dts = av_rescale_q_rnd(packet->dts, iStream->time_base, oStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
//        packet->duration = av_rescale_q(packet->duration, iStream->time_base, oStream->time_base);
//        packet->pos = -1;
//        packet->stream_index = 0;

//        if (av_interleaved_write_frame(oFormatContext, packet) < 0)
//        {
//            qDebug() << "Error muxing packet";
//            break;
//        }
//        av_packet_unref(packet);
//    }

////    av_bitstream_filter_close(h264bsfc);

//    // Write Trailer
//    av_write_trailer(oFormatContextV);
//    av_write_trailer(oFormatContextA);
//    qDebug() << "Demuxer Successful.";

//    avformat_close_input(&iFormatContext);
//    if (oFormatContextV && !(oFormatContextV->oformat->flags & AVFMT_NOFILE))
//        avio_close(oFormatContextV->pb);
//    if (oFormatContextA && !(oFormatContextA->oformat->flags & AVFMT_NOFILE))
//        avio_close(oFormatContextA->pb);
//    avformat_free_context(oFormatContextV);
//    avformat_free_context(oFormatContextA);
//    return true;
//}

//bool HTestMedia::muxer(QString iFileNameV, QString iFileNameA, QString oFileName)
//{
//    if (iFileNameV.isEmpty())
//        iFileNameV = "media\\cuc_ieschool.h264";
//    if (iFileNameA.isEmpty())
//        iFileNameA = "media\\huoyuanjia.mp3";
//    if (oFileName.isEmpty())
//        oFileName = "output.mp4";

//    // Input Video
//    auto iFormatContextV = HFFmpegUtil::createFormatContext(iFileNameV);
//    if (iFormatContextV == nullptr)
//        return false;
//    auto videoIndex = av_find_best_stream(iFormatContextV, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
//    if (videoIndex < 0)
//    {
//        qDebug() << QString("Couldn't find %1 stream.").arg(av_get_media_type_string(AVMEDIA_TYPE_VIDEO));
//        return false;
//    }
//    av_dump_format(iFormatContextV, 0, iFileNameV.toStdString().data(), 0);
//    // Input Audio
//    auto iFormatContextA = HFFmpegUtil::createFormatContext(iFileNameA);
//    if (iFormatContextA == nullptr)
//        return false;
//    auto audioIndex = av_find_best_stream(iFormatContextA, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);
//    if (audioIndex < 0)
//    {
//        qDebug() << QString("Couldn't find %1 stream.").arg(av_get_media_type_string(AVMEDIA_TYPE_AUDIO));
//        return false;
//    }
//    av_dump_format(iFormatContextA, 0, iFileNameA.toStdString().data(), 0);
//    // Output
//    auto codecpars = QList<AVCodecParameters *>() << iFormatContextV->streams[videoIndex]->codecpar
//                                                  << iFormatContextA->streams[audioIndex]->codecpar;
//    auto oFormatContext = HFFmpegUtil::createFormatContext(oFileName, codecpars);
//    if (oFormatContext == nullptr)
//        return false;
//    av_dump_format(oFormatContext, 0, oFileName.toStdString().data(), 1);

//    // Write Header
//    if (avformat_write_header(oFormatContext, nullptr) < 0)
//    {
//        qDebug() << "Error occurred when opening video output file.";
//        return false;
//    }
//    // Write Content
////    auto h264bsfc =  av_bitstream_filter_init("h264_mp4toannexb");
////    auto aacbsfc =  av_bitstream_filter_init("aac_adtstoasc");
//    auto packet = av_packet_alloc();
//    int index = 0;
//    int t = 0;
//    int64_t cur_pts_v = 0, cur_pts_a = 0;
//    while (1)
//    {
//        AVFormatContext *iFormatContext = nullptr;
//        AVStream *iStream = nullptr;
//        AVStream *oStream = nullptr;

//        if (av_compare_ts(cur_pts_v, iFormatContextV->streams[videoIndex]->time_base, cur_pts_a, iFormatContextA->streams[audioIndex]->time_base) <= 0)
//        {
//            iFormatContext = iFormatContextV;
//            oStream = oFormatContext->streams[0];
//            if (av_read_frame(iFormatContext, packet) >= 0)
//            {
//                do {
//                    iStream  = iFormatContext->streams[packet->stream_index];
//                    if (packet->stream_index == videoIndex)
//                    {
//                        if (HFFmpegUtil::fixNoPts(packet, iStream, index))
//                            index++;
//                        cur_pts_v = packet->pts;
//                        break;
//                    }
//                } while (av_read_frame(iFormatContext, packet) >= 0);
//            }
//            else
//            {
//                break;
//            }
//        }
//        else
//        {
//            iFormatContext = iFormatContextA;
//            oStream = oFormatContext->streams[1];
//            if (av_read_frame(iFormatContext, packet) >= 0)
//            {
//                do {
//                    iStream = iFormatContext->streams[packet->stream_index];
//                    if (packet->stream_index == audioIndex)
//                    {
//                        if (HFFmpegUtil::fixNoPts(packet, iStream, index))
//                            index++;
//                        cur_pts_a = packet->pts;
//                        break;
//                    }
//                } while (av_read_frame(iFormatContext, packet) >= 0);
//            }
//            else
//            {
//                break;
//            }
//        }
//        //FIX:Bitstream Filter
////        av_bitstream_filter_filter(h264bsfc, inStream->codec, nullptr, &packet->data, &packet->size, packet->data, packet->size, 0);
////        av_bitstream_filter_filter(aacbsfc, outStream->codec, nullptr, &packet->data, &packet->size, packet->data, packet->size, 0);

//        // Convert PTS/DTS
//        packet->pts = av_rescale_q_rnd(packet->pts, iStream->time_base, oStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
//        packet->dts = av_rescale_q_rnd(packet->dts, iStream->time_base, oStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
//        packet->duration = av_rescale_q(packet->duration, iStream->time_base, oStream->time_base);
//        packet->pos = -1;
//        packet->stream_index = oStream->index;
//        qDebug() << QString("Write %3 Packet. size:%1    pts:%2.").arg(packet->size, 5).arg(packet->pts, 11).arg(t++);

//        if (av_interleaved_write_frame(oFormatContext, packet) < 0)
//        {
//            qDebug() << "Error muxing packet";
//            break;
//        }
//        av_packet_unref(packet);
//    }

////    av_bitstream_filter_close(h264bsfc);
////    av_bitstream_filter_close(aacbsfc);

//    //Write Trailer
//    av_write_trailer(oFormatContext);

//    avformat_close_input(&iFormatContextV);
//    avformat_close_input(&iFormatContextA);
//    if (oFormatContext && !(oFormatContext->oformat->flags & AVFMT_NOFILE))
//        avio_close(oFormatContext->pb);
//    avformat_free_context(oFormatContext);
//    return true;
//}

//bool HTestMedia::streamer(QString iFileName, QString oFileName)
//{
//    if (iFileName.isEmpty())
//        iFileName = "media\\cuc_ieschool.flv";
//    if (oFileName.isEmpty())
//        oFileName = "rtmp://localhost/publishlive/livestream";    // 输出 URL（Output URL）[RTMP]
//        //outFileName = "rtp://233.233.233.233:6666";               // 输出 URL（Output URL）[UDP]

//    avformat_network_init();
//    // Input
//    auto iFormatContext = HFFmpegUtil::createFormatContext(iFileName);
//    if (iFormatContext == nullptr)
//        return false;
//    auto videoIndex = av_find_best_stream(iFormatContext, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
//    if (videoIndex < 0)
//    {
//        qDebug() << QString("Couldn't find %1 stream.").arg(av_get_media_type_string(AVMEDIA_TYPE_VIDEO));
//        return false;
//    }
//    av_dump_format(iFormatContext, 0, iFileName.toStdString().data(), 0);

//    // Output
//    auto oFormatContext = HFFmpegUtil::createFormatContext(oFileName, iFormatContext->streams[videoIndex]->codecpar);
//    if (oFormatContext == nullptr)
//        return false;
//    av_dump_format(oFormatContext, 0, oFileName.toStdString().data(), 1);

//    // Write Header
//    if (avformat_write_header(oFormatContext, nullptr) < 0)
//    {
//        qDebug() << "Error occurred when opening video output file.";
//        return false;
//    }
//    // Write Content
//    auto packet = av_packet_alloc();
//    auto start = av_gettime();
//    auto frameIndex = 0;
//    while (av_read_frame(iFormatContext, packet) >= 0)
//    {
//        HFFmpegUtil::fixNoPts(packet, iFormatContext->streams[videoIndex], frameIndex);

//        if (packet->stream_index == videoIndex)
//        {
//            AVRational time_base = iFormatContext->streams[videoIndex]->time_base;
//            AVRational time_base_q = { 1, AV_TIME_BASE };
//            int64_t pts = av_rescale_q(packet->dts, time_base, time_base_q);
//            int64_t now = av_gettime() - start;
//            if (pts > now)
//                av_usleep(pts - now);
//            qDebug() << QString("Send %1 video frames to output URL.").arg(frameIndex);
//            frameIndex++;
//        }
//        auto iStream  = iFormatContext->streams[packet->stream_index];
//        auto oStream = oFormatContext->streams[packet->stream_index];
//        packet->pts = av_rescale_q_rnd(packet->pts, iStream->time_base, oStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
//        packet->dts = av_rescale_q_rnd(packet->dts, iStream->time_base, oStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
//        packet->duration = av_rescale_q(packet->duration, iStream->time_base, oStream->time_base);
//        packet->pos = -1;
//        if (av_interleaved_write_frame(oFormatContext, packet) < 0)
//        {
//            qDebug() << "Error muxing packet.";
//            return false;
//        }
//        av_packet_unref(packet);
//    }
//    //Write Trailer
//    av_write_trailer(oFormatContext);

//    avformat_close_input(&iFormatContext);
//    if (oFormatContext && !(oFormatContext->oformat->flags & AVFMT_NOFILE))
//        avio_close(oFormatContext->pb);
//    avformat_free_context(oFormatContext);
//    return true;
//}

//bool HTestMedia::receiver(QString iFileName, QString oFileName)
//{
//    if (iFileName.isEmpty())
//        iFileName = "rtmp://live.hkstv.hk.lxdns.com/live/hks";
//    if (oFileName.isEmpty())
//        oFileName = "output.flv";
//    avformat_network_init();

//    // Input
//    auto iFormatContext = HFFmpegUtil::createFormatContext(iFileName);
//    if (iFormatContext == nullptr)
//        return false;
//    auto videoIndex = av_find_best_stream(iFormatContext, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
//    if (videoIndex < 0)
//    {
//        qDebug() << QString("Couldn't find %1 stream.").arg(av_get_media_type_string(AVMEDIA_TYPE_VIDEO));
//        return false;
//    }
//    av_dump_format(iFormatContext, 0, iFileName.toStdString().data(), 0);

//    // Output
//    auto oFormatContext = HFFmpegUtil::createFormatContext(oFileName, iFormatContext->streams[videoIndex]->codecpar);
//    if (oFormatContext == nullptr)
//        return false;
//    av_dump_format(oFormatContext, 0, oFileName.toStdString().data(), 1);

//    // Write Header
//    if (avformat_write_header(oFormatContext, nullptr) < 0)
//    {
//        qDebug() << "Error occurred when opening video output file.";
//        return false;
//    }
//    // Write Content
////    auto h264bsfc =  av_bitstream_filter_init("h264_mp4toannexb");
//    auto packet = av_packet_alloc();
//    auto frameIndex = 0;
//    while (av_read_frame(iFormatContext, packet) >= 0)
//    {
//        auto iStream  = iFormatContext->streams[packet->stream_index];
//        auto oStream = oFormatContext->streams[packet->stream_index];
//        packet->pts = av_rescale_q_rnd(packet->pts, iStream->time_base, oStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
//        packet->dts = av_rescale_q_rnd(packet->dts, iStream->time_base, oStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
//        packet->duration = av_rescale_q(packet->duration, iStream->time_base, oStream->time_base);
//        packet->pos = -1;
//        if(packet->stream_index == videoIndex)
//        {
//            qDebug() << QString("Receive %1 video frames from input URL.").arg(frameIndex++);
////            av_bitstream_filter_filter(h264bsfc, iStream->codec, nullptr, &packet->data, &packet->size, packet->data, packet->size, 0);
//        }
//        if (av_interleaved_write_frame(oFormatContext, packet) < 0)
//        {
//            qDebug() << "Error muxing packet.";
//            return false;
//        }
//        av_packet_unref(packet);
//    }

////    av_bitstream_filter_close(h264bsfc);
//    //Write Trailer
//    av_write_trailer(oFormatContext);

//    avformat_close_input(&iFormatContext);
//    if (oFormatContext && !(oFormatContext->oformat->flags & AVFMT_NOFILE))
//        avio_close(oFormatContext->pb);
//    avformat_free_context(oFormatContext);
//    return true;
//}

//bool HTestMedia::videoFilter(QString fileName, QString filters)
//{
//    if (fileName.isEmpty())
//        fileName = "media\\cuc_ieschool.flv";
//    if (filters.isEmpty())
//        filters = "movie=my_logo.png[wm];[in][wm]overlay=5:5[out]";
//    //const char *filter_descr = "lutyuv='u=128:v=128'";
//    //const char *filter_descr = "boxblur";
//    //const char *filter_descr = "hflip";
//    //const char *filter_descr = "hue='h=60:s=-3'";
//    //const char *filter_descr = "crop=2/3*in_w:2/3*in_h";
//    //const char *filter_descr = "drawbox=x=100:y=100:w=100:h=100:color=pink@0.5";
//    //const char *filter_descr = "drawtext=fontfile=arial.ttf:fontcolor=green:fontsize=30:text='Lei Xiaohua'";

//    //------------FFmpeg----------------
//    auto formatContext = HFFmpegUtil::createFormatContext(fileName);
//    if (formatContext == nullptr)
//        return false;
//    auto index = -1;
//    auto codecContext = HFFmpegUtil::createCodecContext(formatContext, AVMEDIA_TYPE_VIDEO, nullptr, &index);
//    if (codecContext == nullptr)
//        return false;
//    av_dump_format(formatContext, 0, fileName.toStdString().data(), 0);

//    auto list = HFFmpegUtil::createFilterContext(codecContext, formatContext->streams[index], filters);
//    if (list.isEmpty())
//        return false;

//    //------------SDL----------------
//    SDL_Rect rect;
//    rect.x = 0;
//    rect.y = 0;
//    rect.w = codecContext->width;
//    rect.h = codecContext->height;
//    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
//    {
//        qDebug() << QString( "Couldn't initialize SDL - %1.").arg(SDL_GetError());
//        return false;
//    }
//    auto window = SDL_CreateWindow("Simplest FFmpeg Video Filter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, codecContext->width, codecContext->height, SDL_WINDOW_OPENGL);
//    if (!window)
//    {
//        qDebug() << QString( "Couldn't create window - exiting: %1.").arg(SDL_GetError());
//        return false;
//    }
//    auto renderer = SDL_CreateRenderer(window, -1, 0);
//    auto texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, codecContext->width, codecContext->height);

//    //------------PLAY----------------
//    auto display = [=](AVFrame *frame)
//    {
//        updateSDL(texture, renderer, rect, frame->data, frame->linesize);
//        SDL_Delay(40);
//        return true;
//    };
//    auto handle = [=](AVFrame *frame)
//    {
//        frame->pts = frame->best_effort_timestamp;
//        return HFFmpegUtil::filter(list, frame, display);
//    };
//    auto packet = av_packet_alloc();
//    while (av_read_frame(formatContext, packet) >= 0)
//    {
//        if (packet->stream_index == index)
//        {
//            if (!HFFmpegUtil::decodePacket(codecContext, packet, handle))
//                return false;
//        }
//        av_packet_unref(packet);
//    }

//    avcodec_free_context(&codecContext);
//    avformat_close_input(&formatContext);
//    return true;
//}

//bool HTestMedia::videoScale(QString iFileName, QString oFileName)
//{
//    if (iFileName.isEmpty())
//        iFileName = "media\\sintel_480x272_yuv420p.yuv";
//    if (oFileName.isEmpty())
//        oFileName = "output.rgb";

//    // src
//    AVPixelFormat srcPixfmt = AV_PIX_FMT_YUV420P;
//    auto srcW = 480;
//    auto srcH = 272;
//    auto srcSize = srcW * srcH;
//    auto srcBpp = av_get_bits_per_pixel(av_pix_fmt_desc_get(srcPixfmt));
//    auto srcFile = fopen(iFileName.toStdString().data(), "rb");
//    // dst
//    AVPixelFormat dstPixfmt = AV_PIX_FMT_RGB24;
//    auto dstW = 1280;
//    auto dstH = 720;
//    auto dstSize = dstW * dstH;
//    auto dstFile = fopen(oFileName.toStdString().data(), "wb");
//    // Structures
//    uint8_t *srcData[4];
//    uint8_t *dstData[4];
//    int srcLinesize[4];
//    int dstLinesize[4];
//    if (av_image_alloc(srcData, srcLinesize, srcW, srcH, srcPixfmt, 1) < 0)
//    {
//        qDebug() << "Could not allocate source image.";
//        return false;
//    }
//    if (av_image_alloc(dstData, dstLinesize, dstW, dstH, dstPixfmt, 1) < 0)
//    {
//        qDebug() << "Could not allocate destination image.";
//        return false;
//    }
//    // Init Method 1
//    auto swsContext = sws_alloc_context();
////    av_opt_show2(img_convert_ctx, stdout, AV_OPT_FLAG_VIDEO_PARAM, 0);
//    av_opt_set_int(swsContext, "sws_flags", SWS_BICUBIC|SWS_PRINT_INFO, 0);
//    av_opt_set_int(swsContext, "srcw", srcW, 0);
//    av_opt_set_int(swsContext, "srch", srcH, 0);
//    av_opt_set_int(swsContext, "src_format", srcPixfmt, 0);  //'0' for MPEG (Y:0-235);'1' for JPEG (Y:0-255)
//    av_opt_set_int(swsContext, "src_range", 1, 0);
//    av_opt_set_int(swsContext, "dstw", dstW, 0);
//    av_opt_set_int(swsContext, "dsth" ,dstH, 0);
//    av_opt_set_int(swsContext, "dst_format", dstPixfmt, 0);
//    av_opt_set_int(swsContext, "dst_range", 1, 0);
//    if (sws_init_context(swsContext, nullptr, nullptr) < 0)
//    {
//        qDebug() << "Could not init context.";
//        return false;
//    }
////    //Init Method 2
////    auto img_convert_ctx = sws_getContext(srcW, srcH, srcPixfmt,
////                                            dstW, dstH, dstPixfmt,
////                                            SWS_BICUBIC, nullptr, nullptr, nullptr);

////    //Colorspace
////    if (sws_setColorspaceDetails(img_convert_ctx,
////                                 sws_getCoefficients(SWS_CS_ITU601), 0,
////                                 sws_getCoefficients(SWS_CS_ITU709), 0,
////                                 0, 1 << 16, 1 << 16) < 0)
////    {
////        qDebug() << "Colorspace not support.";
////        return false;
////    }


//    size_t bufferSize = srcSize * srcBpp / 8;
//    auto buffer = (uint8_t *)malloc(bufferSize);
//    auto index = 0;
//    while (1)
//    {
//        if (fread(buffer, 1, bufferSize, srcFile) != bufferSize)
//            break;

//        switch(srcPixfmt)
//        {
//        case AV_PIX_FMT_GRAY8:
//            memcpy(srcData[0], buffer, srcSize);
//            break;
//        case AV_PIX_FMT_YUV420P:
//            memcpy(srcData[0], buffer, srcSize);
//            memcpy(srcData[1], buffer + srcSize, srcSize / 4);
//            memcpy(srcData[2], buffer + srcSize * 5 / 4, srcSize / 4);
//            break;
//        case AV_PIX_FMT_YUV422P:
//            memcpy(srcData[0], buffer, srcSize);
//            memcpy(srcData[1], buffer + srcSize, srcSize / 2);
//            memcpy(srcData[2], buffer + srcSize * 3 / 2, srcSize / 2);
//            break;
//        case AV_PIX_FMT_YUV444P:
//            memcpy(srcData[0], buffer, srcSize);
//            memcpy(srcData[1], buffer + srcSize, srcSize);
//            memcpy(srcData[2], buffer + srcSize * 2, srcSize);
//            break;
//        case AV_PIX_FMT_YUYV422:
//            memcpy(srcData[0], buffer, srcSize * 2);
//            break;
//        case AV_PIX_FMT_RGB24:
//            memcpy(srcData[0], buffer, srcSize * 3);
//            break;
//        default:
//            qDebug() << "Not Support Input Pixel Format.";
//            break;
//        }

//        sws_scale(swsContext, srcData, srcLinesize, 0, srcH, dstData, dstLinesize);
//        qDebug() << QString("Finish process frame %1.").arg(index++);

//        switch(dstPixfmt)
//        {
//        case AV_PIX_FMT_GRAY8:
//            fwrite(dstData[0], 1, dstSize, dstFile);
//            break;
//        case AV_PIX_FMT_YUV420P:
//            fwrite(dstData[0], 1, dstSize, dstFile);
//            fwrite(dstData[1], 1, dstSize / 4, dstFile);
//            fwrite(dstData[2], 1, dstSize / 4, dstFile);
//            break;
//        case AV_PIX_FMT_YUV422P:
//            fwrite(dstData[0], 1, dstSize, dstFile);
//            fwrite(dstData[1], 1, dstSize / 2,dstFile);
//            fwrite(dstData[2], 1, dstSize / 2,dstFile);
//            break;
//        case AV_PIX_FMT_YUV444P:
//            fwrite(dstData[0], 1, dstSize, dstFile);
//            fwrite(dstData[1], 1, dstSize, dstFile);
//            fwrite(dstData[2], 1, dstSize,dstFile);
//            break;
//        case AV_PIX_FMT_YUYV422:
//            fwrite(dstData[0], 1, dstSize * 2, dstFile);
//            break;
//        case AV_PIX_FMT_RGB24:
//            fwrite(dstData[0], 1, dstSize * 3, dstFile);
//            break;
//        default:
//            qDebug() << "Not Support Output Pixel Format.";
//            break;
//        }
//    }

//    sws_freeContext(swsContext);
//    free(buffer);
//    fclose(srcFile);
//    fclose(dstFile);
//    av_freep(&srcData[0]);
//    av_freep(&dstData[0]);
//    return true;
//}

//bool HTestMedia::grabDesktop()
//{
//    AVDictionary *options = nullptr;
//#if USE_DSHOW
//    // Use dshow
//    //
//    // Need to Install screen-capture-recorder
//    // Website: http://sourceforge.net/projects/screencapturer/
//    //
//    auto name = "dshow";
//    auto url = "video=screen-capture-recorder";
//#else
//    auto name = "gdigrab";
//    auto url = "desktop";
//    av_dict_set(&options, "framerate", "5", 0);
//    av_dict_set(&options, "offset_x", "20", 0);
//    av_dict_set(&options, "offset_y", "40", 0);
//    av_dict_set(&options, "video_size", "640x480", 0);
//#endif
//    avformat_network_init();
//    avdevice_register_all();
//    auto formatContext = HFFmpegUtil::createFormatContext(url, name, options);
//    if (formatContext == nullptr)
//        return false;
//    auto index = -1;
//    auto codecContext = HFFmpegUtil::createCodecContext(formatContext, AVMEDIA_TYPE_VIDEO, nullptr, &index);
//    if (codecContext == nullptr)
//        return false;
//    av_dump_format(formatContext, 0, url, 0);

//    if (displaySDL(formatContext, codecContext, index, "Simplest ffmpeg Grab Desktop"))
//        return false;

//    avcodec_close(codecContext);
//    avformat_close_input(&formatContext);
//    return true;
//}

//bool HTestMedia::readCamera()
//{
//#if USE_DSHOW
//    // Use dshow
//    //
//    // Need to Install screen-capture-recorder
//    // Website: http://sourceforge.net/projects/screencapturer/
//    //
//    auto name = "dshow";
//    auto url = "video=Integrated Camera";
//#else
//    auto name = "vfwcap";
//    auto url = "0";
//#endif
//    avformat_network_init();
//    avdevice_register_all();
//    auto formatContext = HFFmpegUtil::createFormatContext(url, name, nullptr);
//    if (formatContext == nullptr)
//        return false;
//    auto index = -1;
//    auto codecContext = HFFmpegUtil::createCodecContext(formatContext, AVMEDIA_TYPE_VIDEO, nullptr, &index);
//    if (codecContext == nullptr)
//        return false;
//    av_dump_format(formatContext, 0, url, 0);

//    if (displaySDL(formatContext, codecContext, index, "Simplest ffmpeg read camera"))
//        return false;

//    avcodec_close(codecContext);
//    avformat_close_input(&formatContext);
//    return true;
//}

//FILE *__fileRead = nullptr;

//int readBuffer(void */*opaque*/, uint8_t *buffer, int size)
//{
//    if(!feof(__fileRead))
//        return fread(buffer, 1, size, __fileRead);
//    return -1;
//}

//bool HTestMedia::memPlayer(QString fileName)
//{
//    if (fileName.isEmpty())
//        fileName = "media\\cuc60anniversary_start.mkv";

//    avformat_network_init();

//    __fileRead = fopen(fileName.toStdString().data(), "rb+");
//    //Init AVIOContext
//    auto avioBuffer = (unsigned char *)av_malloc(32768);
//    auto formatContext = avformat_alloc_context();
//    formatContext->pb = avio_alloc_context(avioBuffer, 32768, 0, nullptr, readBuffer, nullptr, nullptr);
//    if (avformat_open_input(&formatContext, nullptr, nullptr, nullptr)!=0)
//    {
//        qDebug() << "Couldn't open input stream.";
//        return false;
//    }
//    if (avformat_find_stream_info(formatContext, nullptr) < 0)
//    {
//        qDebug() << "Couldn't find stream information.";
//        return false;
//    }
//    auto index = -1;
//    auto codecContext = HFFmpegUtil::createCodecContext(formatContext, AVMEDIA_TYPE_VIDEO, nullptr, &index);
//    if (codecContext == nullptr)
//        return false;
//    av_dump_format(formatContext, 0, "Mem", 0);

//    if (displaySDL(formatContext, codecContext, index, "Simplest ffmpeg Grab Desktop"))
//        return false;

//    fclose(__fileRead);
//    avcodec_close(codecContext);
//    avformat_close_input(&formatContext);
//    return true;
//}
