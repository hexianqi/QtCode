#include "HTestMedia.h"
#include <QtCore/QFile>
#include <QtCore/QDataStream>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/imgutils.h"
#include "libavutil/opt.h"
#include "libswscale/swscale.h"
#include "libswresample/swresample.h"
#include "SDL2/SDL.h"
};

#define SFM_REFRESH_EVENT       (SDL_USEREVENT + 1)
#define SFM_BREAK_EVENT         (SDL_USEREVENT + 2)
#define MAX_AUDIO_FRAME_SIZE    192000                  // 1 second of 48khz 32bit audio
#define printf qDebug

void outputYUV(FILE *file, AVFrame *frame, int ysize)
{
    if (file == nullptr)
        return;
    fwrite(frame->data[0], 1, ysize, file);
    fwrite(frame->data[1], 1, ysize / 4, file);
    fwrite(frame->data[2], 1, ysize / 4, file);
}

void updateSDL(SDL_Texture *texture, SDL_Renderer *renderer, SDL_Rect rect, AVFrame *frame)
{
    SDL_UpdateYUVTexture(texture, nullptr,
                         frame->data[0], frame->linesize[0],
                         frame->data[1], frame->linesize[1],
                         frame->data[2], frame->linesize[2]);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
    SDL_RenderPresent(renderer);
}

bool __threadExit = false;
bool __threadPause = false;

int sfpRefreshThread(void */*opaque*/)
{
    __threadExit = false;
    __threadPause = false;

    while (!__threadExit)
    {
        if(!__threadPause)
        {
            // Refresh
            SDL_Event event;
            event.type = SFM_REFRESH_EVENT;
            SDL_PushEvent(&event);
        }
        SDL_Delay(40);
    }
    __threadExit = false;
    __threadPause = false;
    // Break
    SDL_Event event;
    event.type = SFM_BREAK_EVENT;
    SDL_PushEvent(&event);

    return 0;
}

//Buffer:
//|-----------|-------------|
//chunk-------pos---len-----|
static Uint8 *__audioChunk;
static Uint8 *__audioPos;
static int __audioLen;

// The audio function callback takes the following parameters:
// stream: A pointer to the audio buffer to be filled
// len: The length (in bytes) of the audio buffer
void fillAudio(void */*userdata*/, Uint8 *stream, int len)
{
    SDL_memset(stream, 0, len);
    if (__audioLen == 0)
        return;

    if (len > __audioLen)
        len = __audioLen;

    SDL_MixAudio(stream, __audioPos, len, SDL_MIX_MAXVOLUME);
    __audioPos += len;
    __audioLen -= len;
}

bool flushEncoder(AVFormatContext *formatContext, AVCodecContext *codecContext)
{
    if (!(codecContext->codec->capabilities & AV_CODEC_CAP_DELAY))
        return true;

    auto packet = av_packet_alloc();
    av_new_packet(packet, 0);
    if (avcodec_send_frame(codecContext, nullptr) < 0)
        return false;
    while (avcodec_receive_packet(codecContext, packet) == 0)
    {
        printf("Flush Encoder: Succeed to encode 1 frame!\tsize:%5d\n", packet->size);
        if (av_write_frame(formatContext, packet) < 0)
            return false;
        av_packet_unref(packet);
    }
    return true;
}

bool HTestMedia::videoPlayer(QString fileName, bool output)
{
    if (fileName.isEmpty())
        fileName = "media\\Titanic.ts";

    //------------FFmpeg----------------
    avformat_network_init();
    auto formatContext = avformat_alloc_context();
    if (avformat_open_input(&formatContext, fileName.toStdString().data(), nullptr, nullptr) !=0 )
    {
        printf("Couldn't open input stream.\n");
        return false;
    }

    if (avformat_find_stream_info(formatContext, nullptr) < 0 )
    {
        printf("Couldn't find stream information.\n");
        return false;
    }

    av_dump_format(formatContext, 0, fileName.toStdString().data(), 0);

    auto index = av_find_best_stream(formatContext, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
    if (index < 0)
    {
        printf("Couldn't find a video stream.\n");
        return false;
    }

    auto codecContext = avcodec_alloc_context3(nullptr);
    if (avcodec_parameters_to_context(codecContext, formatContext->streams[index]->codecpar) != 0)
    {
        printf("Couldn't copy codec context.\n");
        return false;
    }

    auto decoder = avcodec_find_decoder(codecContext->codec_id);
    if (decoder == nullptr)
    {
        printf("Couldn't find video decoder.\n");
        return false;
    }

    if (avcodec_open2(codecContext, decoder, nullptr) < 0)
    {
        printf("Couldn't open video codec.\n");
        return false;
    }

    auto packet = av_packet_alloc();
    auto frame = av_frame_alloc();
    auto frameYUV = av_frame_alloc();
    auto width = codecContext->width;
    auto height = codecContext->height;
    auto ysize = codecContext->width * codecContext->height;
    auto buffer = (unsigned char *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_YUV420P,  width, height, 1));
    av_image_fill_arrays(frameYUV->data, frameYUV->linesize, buffer, AV_PIX_FMT_YUV420P, width, height, 1);
    auto swsContext = sws_getContext(width, height, codecContext->pix_fmt,
                                     width, height, AV_PIX_FMT_YUV420P,
                                     SWS_BICUBIC, nullptr, nullptr, nullptr);

    //------------Output----------------
    FILE *file = nullptr;
    if (output)
        file = fopen("output.yuv","wb+");

    //------------SDL----------------
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = height;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
    {
        printf( "Couldn't initialize SDL - %s\n", SDL_GetError());
        return false;
    }

    auto window = SDL_CreateWindow("Simplest ffmpeg player's Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    if (!window)
    {
        printf("Couldn't create window - exiting:%s\n", SDL_GetError());
        return false;
    }
    auto renderer = SDL_CreateRenderer(window, -1, 0);
    auto texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, width, height);

    //------------PLAY----------------
    while (av_read_frame(formatContext, packet) >=0)
    {
        if (packet->stream_index == index)
        {
            if (avcodec_send_packet(codecContext, packet) < 0)
            {
                printf("Decode Error.\n");
                return false;
            }
            while (avcodec_receive_frame(codecContext, frame) == 0)
            {
                sws_scale(swsContext, (const unsigned char* const*)frame->data, frame->linesize, 0, height, frameYUV->data, frameYUV->linesize);
                outputYUV(file, frameYUV, ysize);
                updateSDL(texture, renderer, rect, frameYUV);
                SDL_Delay(40);
            }
        }
        av_packet_unref(packet);
    }
    // flush decoder
    // FIX: Flush Frames remained in Codec
    while (1)
    {
        if (avcodec_send_packet(codecContext, packet) != 0)
            break;
        while (avcodec_receive_frame(codecContext, frame) == 0)
        {
            sws_scale(swsContext, (const unsigned char* const*)frame->data, frame->linesize, 0, height, frameYUV->data, frameYUV->linesize);
            outputYUV(file, frameYUV, ysize);
            updateSDL(texture, renderer, rect, frameYUV);
            SDL_Delay(40);
        }
    }

    //------------Free----------------
    if (file != nullptr)
        fclose(file);
    sws_freeContext(swsContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    av_frame_free(&frameYUV);
    av_frame_free(&frame);
    avcodec_close(codecContext);
    avformat_close_input(&formatContext);
    return true;
}

bool HTestMedia::videoPlayer_SU(QString fileName)
{
    if (fileName.isEmpty())
        fileName = "media\\Titanic.ts";

    //------------FFmpeg----------------
    avformat_network_init();
    auto formatContext = avformat_alloc_context();
    if (avformat_open_input(&formatContext, fileName.toStdString().data(), nullptr, nullptr) !=0 )
    {
        printf("Couldn't open input stream.\n");
        return false;
    }

    if (avformat_find_stream_info(formatContext, nullptr) < 0 )
    {
        printf("Couldn't find stream information.\n");
        return false;
    }

    av_dump_format(formatContext,0, fileName.toStdString().data(), 0);

    auto index = av_find_best_stream(formatContext, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);
    if (index < 0)
    {
        printf("Couldn't find a video stream.\n");
        return false;
    }

    auto codecContext = avcodec_alloc_context3(nullptr);
    if (avcodec_parameters_to_context(codecContext, formatContext->streams[index]->codecpar) != 0)
    {
        printf("Couldn't copy codec context.\n");
        return false;
    }

    auto decoder = avcodec_find_decoder(codecContext->codec_id);
    if (decoder == nullptr)
    {
        printf("Couldn't find video decoder.\n");
        return false;
    }

    if (avcodec_open2(codecContext, decoder, nullptr) < 0)
    {
        printf("Couldn't open video codec.\n");
        return false;
    }

    auto packet = av_packet_alloc();
    auto frame = av_frame_alloc();
    auto frameYUV = av_frame_alloc();
    auto width = codecContext->width;
    auto height = codecContext->height;
    auto buffer = (unsigned char *)av_malloc(av_image_get_buffer_size(AV_PIX_FMT_YUV420P,  width, height, 1));
    av_image_fill_arrays(frameYUV->data, frameYUV->linesize, buffer, AV_PIX_FMT_YUV420P, width, height, 1);
    auto swsContext = sws_getContext(width, height, codecContext->pix_fmt,
                                     width, height, AV_PIX_FMT_YUV420P,
                                     SWS_BICUBIC, nullptr, nullptr, nullptr);

    //------------SDL----------------
    SDL_Event event;
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = width;
    rect.h = height;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
    {
        printf( "Couldn't initialize SDL - %s\n", SDL_GetError());
        return false;
    }

    auto window = SDL_CreateWindow("Simplest ffmpeg player's Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    if (!window)
    {
        printf("Couldn't create window - exiting:%s\n", SDL_GetError());
        return false;
    }
    auto renderer = SDL_CreateRenderer(window, -1, 0);
    auto texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, width, height);

    SDL_CreateThread(sfpRefreshThread, nullptr, nullptr);
    //------------Event Loop----------------
    for (;;)
    {
        SDL_WaitEvent(&event);
        if (event.type == SFM_REFRESH_EVENT)
        {
            while (1)
            {
                if (av_read_frame(formatContext, packet) < 0)
                    __threadExit = true;

                if (packet->stream_index == index)
                    break;
            }
            avcodec_send_packet(codecContext, packet);
            while (avcodec_receive_frame(codecContext, frame) == 0)
            {
                sws_scale(swsContext, (const unsigned char* const*)frame->data, frame->linesize, 0, height, frameYUV->data, frameYUV->linesize);
                updateSDL(texture, renderer, rect, frameYUV);
            }
            av_packet_unref(packet);
        }
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_SPACE)
                __threadPause = !__threadPause;
        }
        else if (event.type==SDL_QUIT)
        {
            __threadExit = true;
        }
        else if (event.type == SFM_BREAK_EVENT)
        {
            break;
        }
    }

    //------------Free----------------
    sws_freeContext(swsContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    av_frame_free(&frameYUV);
    av_frame_free(&frame);
    avcodec_close(codecContext);
    avformat_close_input(&formatContext);
    return true;
}

bool HTestMedia::audioPlayer(QString fileName, bool output)
{
    if (fileName.isEmpty())
        fileName = "media\\xiaoqingge.mp3";

    //------------FFmpeg----------------
    avformat_network_init();
    auto formatContext = avformat_alloc_context();
    if(avformat_open_input(&formatContext,fileName.toStdString().data(), nullptr, nullptr) != 0)
    {
        printf("Couldn't open input stream.\n");
        return false;
    }

    if (avformat_find_stream_info(formatContext, nullptr) < 0 )
    {
        printf("Couldn't find stream information.\n");
        return false;
    }

    av_dump_format(formatContext,0, fileName.toStdString().data(), 0);

    auto index = av_find_best_stream(formatContext, AVMEDIA_TYPE_AUDIO, -1, -1, nullptr, 0);
    if (index < 0)
    {
        printf("Couldn't find a audio stream.\n");
        return false;
    }

    auto codecContext = avcodec_alloc_context3(nullptr);
    if (avcodec_parameters_to_context(codecContext, formatContext->streams[index]->codecpar) != 0)
    {
        printf("Couldn't copy codec context.\n");
        return false;
    }

    auto decoder = avcodec_find_decoder(codecContext->codec_id);
    if (decoder == nullptr)
    {
        printf("Couldn't find audio decoder.\n");
        return false;
    }

    if (avcodec_open2(codecContext, decoder, nullptr) < 0)
    {
        printf("Couldn't open audio codec.\n");
        return false;
    }

    auto packet = av_packet_alloc();
    auto frame = av_frame_alloc();
    int outSampleRate = 44100;
    uint64_t outChannelLayout = AV_CH_LAYOUT_STEREO;
    AVSampleFormat outSampleFmt = AV_SAMPLE_FMT_S16;
    auto outChannels = av_get_channel_layout_nb_channels(outChannelLayout);
    auto outSamples = codecContext->frame_size;    // nb_samples: AAC-1024 MP3-1152
    auto outBufferSize = av_samples_get_buffer_size(nullptr, outChannels, outSamples, outSampleFmt, 1);
    auto outBuffer = (unsigned char *)av_malloc(MAX_AUDIO_FRAME_SIZE * 2);
    // FIX:Some Codec's Context Information is missing
    auto inChannelLayout = av_get_default_channel_layout(codecContext->channels);
    auto swrContext = swr_alloc_set_opts(nullptr,
                                         outChannelLayout, outSampleFmt, outSampleRate,
                                         inChannelLayout, codecContext->sample_fmt, codecContext->sample_rate,
                                         0, nullptr);
    swr_init(swrContext);

    //------------Output----------------
    FILE *file = nullptr;
    if (output)
        file = fopen("output.pcm","wb+");

    //------------SDL----------------
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
    {
        printf( "Couldn't initialize SDL - %s\n", SDL_GetError());
        return false;
    }

    SDL_AudioSpec spec;
    spec.freq = outSampleRate;
    spec.format = AUDIO_S16SYS;
    spec.channels = outChannels;
    spec.silence = 0;
    spec.samples = outSamples;
    spec.callback = fillAudio;
    spec.userdata = codecContext;
    if (SDL_OpenAudio(&spec, nullptr) < 0)
    {
        printf("Couldn't open audio.\n");
        return -1;
    }

    //------------PLAY----------------
    int frameIndex = 0;
    SDL_PauseAudio(0);
    while (av_read_frame(formatContext, packet) >=0)
    {
        if (packet->stream_index == index)
        {
            if (avcodec_send_packet(codecContext, packet) < 0)
            {
                printf("Decode Error.\n");
                return false;
            }
            while (avcodec_receive_frame(codecContext, frame) == 0)
            {
                swr_convert(swrContext, &outBuffer, MAX_AUDIO_FRAME_SIZE, (const uint8_t **)frame->data , frame->nb_samples);
                printf("index:%5d\t pts:%lld\t packet size:%d\n", frameIndex, packet->pts, packet->size);
                if (file != nullptr)
                    fwrite(outBuffer, 1, outBufferSize, file);
                frameIndex++;
            }

            while(__audioLen > 0) //Wait until finish
                SDL_Delay(1);
            // Set audio buffer (PCM data) buffer length
            __audioChunk = (Uint8 *)outBuffer;
            __audioLen = outBufferSize;
            __audioPos = __audioChunk;
        }
        av_packet_unref(packet);
    }

    //------------Free----------------
    swr_free(&swrContext);
    SDL_CloseAudio();
    SDL_Quit();
    if (file != nullptr)
        fclose(file);
    av_free(outBuffer);
    avcodec_close(codecContext);
    avformat_close_input(&formatContext);
    return true;
}

bool HTestMedia::yuv2jpg(QString inFileName, QString outFileName)
{
    if (inFileName.isEmpty())
        inFileName = "media\\cuc_view_480x272.yuv";
    if (outFileName.isEmpty())
        outFileName = "output.jpg";

    //------------FFmpeg----------------
    AVFormatContext *formatContext;
    avformat_alloc_output_context2(&formatContext, nullptr, nullptr, outFileName.toStdString().data());
    if (avio_open(&formatContext->pb, outFileName.toStdString().data(), AVIO_FLAG_READ_WRITE) < 0)
    {
        printf("Couldn't open output file.\n");
        return false;
    }
    auto codeId = formatContext->oformat->video_codec;
    av_dump_format(formatContext, 0, outFileName.toStdString().data(), 1);

    auto encoder = avcodec_find_encoder(codeId);
    if (encoder == nullptr)
    {
        printf("Couldn't find encoder.\n");
        return false;
    }

    auto stream = avformat_new_stream(formatContext, nullptr);
    if (stream == nullptr)
    {
        printf("Couldn't create stream.\n");
        return false;
    }

    auto codecContext = avcodec_alloc_context3(nullptr);
    codecContext->codec_id = codeId;
    codecContext->codec_type = AVMEDIA_TYPE_VIDEO;
    codecContext->pix_fmt = *encoder->pix_fmts;
    codecContext->width = 480;
    codecContext->height = 272;
    codecContext->time_base.num = 1;
    codecContext->time_base.den = 25;

    if (avcodec_open2(codecContext, encoder, nullptr) < 0)
    {
        printf("Couldn't open encoder.\n");
        return false;
    }

    auto frame = av_frame_alloc();
    frame->format = codecContext->pix_fmt;
    frame->width  = codecContext->width;
    frame->height = codecContext->height;
    auto ysize = codecContext->width * codecContext->height;
    auto buffer = (unsigned char *)av_malloc(av_image_get_buffer_size(codecContext->pix_fmt, codecContext->width, codecContext->height, 1));
    av_image_fill_arrays(frame->data, frame->linesize, buffer, codecContext->pix_fmt, codecContext->width, codecContext->height, 1);
    auto packet = av_packet_alloc();
    av_new_packet(packet, ysize * 3);

    // Write Header
    if (avformat_write_header(formatContext, nullptr) < 0)
    {
        printf("Write Header Error.\n");
    }
    // Read YUV
    auto inFile = fopen(inFileName.toStdString().data(), "rb");
    if (fread(buffer, 1, ysize * 3 / 2, inFile) <=0)
    {
        printf("Could not read input file.");
        return false;
    }
    frame->data[0] = buffer;                   // Y
    frame->data[1] = buffer + ysize;           // U
    frame->data[2] = buffer + ysize * 5 / 4;   // V
    frame->pts = 0;
    // Encode
    if (avcodec_send_frame(codecContext, frame) < 0)
    {
        printf("Encode Error.\n");
        return false;
    }
    while (avcodec_receive_packet(codecContext, packet) == 0)
    {
        packet->stream_index = stream->index;
        av_write_frame(formatContext, packet);
    }
    av_packet_unref(packet);
    // Write Trailer
    av_write_trailer(formatContext);
    printf("Encode Successful.\n");

    //------------Free----------------
    fclose(inFile);
    avcodec_close(codecContext);
    av_free(frame);
    av_free(buffer);
    avio_close(formatContext->pb);
    avformat_free_context(formatContext);
    return true;
}

bool HTestMedia::videoEncoder(QString inFileName, QString outFileName)
{
    if (inFileName.isEmpty())
        inFileName = "media\\ds_480x272.yuv";
    if (outFileName.isEmpty())
        outFileName = "output.h264";

    int frameNum = 100;

    AVFormatContext *formatContext;
    avformat_alloc_output_context2(&formatContext, nullptr, nullptr, outFileName.toStdString().data());
    if (avio_open(&formatContext->pb, outFileName.toStdString().data(), AVIO_FLAG_READ_WRITE) < 0)
    {
        printf("Couldn't open output file.\n");
        return false;
    }

    auto codeId = formatContext->oformat->video_codec;
    av_dump_format(formatContext, 0, outFileName.toStdString().data(), 1);

    auto encoder = avcodec_find_encoder(codeId);
    if (encoder == nullptr)
    {
        printf("Couldn't find encoder.\n");
        return false;
    }

    auto stream = avformat_new_stream(formatContext, nullptr);
    if (stream == nullptr)
    {
        printf("Couldn't create stream.\n");
        return false;
    }
    stream->codecpar->codec_id = codeId;
    stream->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    stream->codecpar->width = 480;
    stream->codecpar->height = 272;
    stream->codecpar->bit_rate = 400000;
    stream->codecpar->format = *encoder->pix_fmts;

    auto codecContext = avcodec_alloc_context3(nullptr);
    if (avcodec_parameters_to_context(codecContext, stream->codecpar) != 0)
    {
        printf("Couldn't copy codec context.\n");
        return false;
    }
    codecContext->gop_size = 250;
    codecContext->time_base.num = 1;
    codecContext->time_base.den = 25;
    codecContext->qmin = 10;
    codecContext->qmax = 51;
    codecContext->max_b_frames = 3;

    // Set Option
    AVDictionary *param = nullptr;
    if (codeId == AV_CODEC_ID_H264)
    {
        av_dict_set(&param, "preset", "slow", 0);
        av_dict_set(&param, "tune", "zerolatency", 0);
    }
    if (codeId == AV_CODEC_ID_H265)
    {
        av_dict_set(&param, "preset", "ultrafast", 0);
        av_dict_set(&param, "tune", "zero-latency", 0);
    }

    if (avcodec_open2(codecContext, encoder, &param) < 0)
    {
        printf("Couldn't open encoder.\n");
        return -1;
    }

    auto frame = av_frame_alloc();
    frame->format = codecContext->pix_fmt;
    frame->width  = codecContext->width;
    frame->height = codecContext->height;
    auto ysize = codecContext->width * codecContext->height;
    auto size = av_image_get_buffer_size(codecContext->pix_fmt, codecContext->width, codecContext->height, 1);
    auto buffer = (unsigned char *)av_malloc(size);
    av_image_fill_arrays(frame->data, frame->linesize, buffer, codecContext->pix_fmt, codecContext->width, codecContext->height, 1);

    // Write Header
    if (avformat_write_header(formatContext, nullptr) < 0)
    {
        printf("Write Header Error.\n");
    }

    auto inFile = fopen(inFileName.toStdString().data(), "rb");
    auto packet = av_packet_alloc();
    av_new_packet(packet, size);
    for (int i = 0; i < frameNum; i++)
    {
        // Read YUV data
        if (fread(buffer, 1, ysize * 3 / 2, inFile) <= 0)
        {
            printf("Failed to read raw data! \n");
            return false;
        }
        else if (feof(inFile))
        {
            break;
        }
        frame->data[0] = buffer;                    // Y
        frame->data[1] = buffer + ysize;            // U
        frame->data[2] = buffer + ysize * 5 / 4;    // V
        frame->pts = i * stream->time_base.den / (stream->time_base.num * 25);
        // Encode
        if (avcodec_send_frame(codecContext, frame) < 0)
        {
            printf("Encode Error.\n");
            return false;
        }
        while (avcodec_receive_packet(codecContext, packet) == 0)
        {
            printf("Succeed to encode frame: %5d\tsize:%5d\n", i, packet->size);
            packet->stream_index = stream->index;
            av_write_frame(formatContext, packet);
            av_packet_unref(packet);
        }
    }
    // Flush Encoder
    if (!flushEncoder(formatContext, codecContext))
    {
        printf("Flushing encoder failed.\n");
        return false;
    }
    // Write  Trailer
    av_write_trailer(formatContext);
    printf("Encode Successful.\n");
    //------------Free----------------
    fclose(inFile);
    avcodec_close(codecContext);
    av_free(frame);
    av_free(buffer);
    avio_close(formatContext->pb);
    avformat_free_context(formatContext);
    return true;
}

bool HTestMedia::audioEncoder(QString inFileName, QString outFileName)
{
    if (inFileName.isEmpty())
        inFileName = "media\\tdjm.pcm";
    if (outFileName.isEmpty())
        outFileName = "output.mp3";

    int frameNum = 1000;

    AVFormatContext *formatContext;
    avformat_alloc_output_context2(&formatContext, nullptr, nullptr, outFileName.toStdString().data());
    if (avio_open(&formatContext->pb, outFileName.toStdString().data(), AVIO_FLAG_READ_WRITE) < 0)
    {
        printf("Couldn't open output file.\n");
        return false;
    }

    auto codeId = formatContext->oformat->audio_codec;
    av_dump_format(formatContext, 0, outFileName.toStdString().data(), 1);

    auto encoder = avcodec_find_encoder(codeId);
    if (encoder == nullptr)
    {
        printf("Couldn't find encoder.\n");
        return false;
    }

    auto stream = avformat_new_stream(formatContext, nullptr);
    if (stream == nullptr)
    {
        printf("Couldn't create stream.\n");
        return false;
    }
    stream->codecpar->codec_id = codeId;
    stream->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
    stream->codecpar->sample_rate = 44100;
    stream->codecpar->channel_layout = AV_CH_LAYOUT_STEREO;
    stream->codecpar->channels = av_get_channel_layout_nb_channels(AV_CH_LAYOUT_STEREO);
    stream->codecpar->bit_rate = 64000;
    stream->codecpar->profile = FF_PROFILE_AAC_MAIN;
    stream->codecpar->format = *encoder->sample_fmts;

    auto codecContext = avcodec_alloc_context3(nullptr);
    if (avcodec_parameters_to_context(codecContext, stream->codecpar) != 0)
    {
        printf("Couldn't copy codec context.\n");
        return false;
    }
    codecContext->strict_std_compliance = FF_COMPLIANCE_EXPERIMENTAL;

    if (avcodec_open2(codecContext, encoder, nullptr) < 0)
    {
        printf("Couldn't open encoder.\n");
        return false;
    }

    auto swrContext = swr_alloc_set_opts(nullptr,
                                         codecContext->channel_layout, codecContext->sample_fmt, codecContext->sample_rate,
                                         AV_CH_LAYOUT_STEREO, AV_SAMPLE_FMT_S16,  44100,
                                         0, nullptr);
    swr_init(swrContext);

    auto frame = av_frame_alloc();
    frame->nb_samples= codecContext->frame_size;
    frame->format= codecContext->sample_fmt;
    auto size = av_samples_get_buffer_size(nullptr, codecContext->channels, codecContext->frame_size, codecContext->sample_fmt, 1);
    auto buffer = (unsigned char *)av_malloc(size);
    avcodec_fill_audio_frame(frame, codecContext->channels, codecContext->sample_fmt,(const uint8_t*)buffer, size, 1);

    // Write Header
    if (avformat_write_header(formatContext, nullptr) < 0)
    {
        printf("Write Header Error.\n");
    }

    uint8_t *outs[2];
    int len = 4096;
    outs[0] = (uint8_t *)malloc(len);
    outs[1] = (uint8_t *)malloc(len);
    auto inFile = fopen(inFileName.toStdString().data(), "rb");
    auto packet = av_packet_alloc();
    av_new_packet(packet, size);
    for (int i = 0; i < frameNum; i++)
    {
        // Read PCM
        if (fread(buffer, 1, size, inFile) <= 0)
        {
            printf("Failed to read raw data! \n");
            return false;
        }
        else if(feof(inFile))
        {
            break;
        }
        swr_convert(swrContext, outs, len * 4, (const uint8_t **)&buffer, len / 4);
        frame->data[0] =(uint8_t*)outs[0];
        frame->data[1] =(uint8_t*)outs[1];
        frame->pts = i * 100;
        // Encode
        if (avcodec_send_frame(codecContext, frame) < 0)
        {
            printf("Encode Error.\n");
            return false;
        }
        while (avcodec_receive_packet(codecContext, packet) == 0)
        {
            printf("Succeed to encode 1 frame! \tsize:%5d\n",packet->size);
            packet->stream_index = stream->index;
            av_write_frame(formatContext, packet);
            av_packet_unref(packet);
        }
    }
    // Flush Encoder
    if (!flushEncoder(formatContext, codecContext))
    {
        printf("Flushing encoder failed.\n");
        return false;
    }
    // Write  Trailer
    av_write_trailer(formatContext);
    printf("Encode Successful.\n");

    fclose(inFile);
    avcodec_close(codecContext);
    av_free(frame);
    av_free(buffer);
    avio_close(formatContext->pb);
    avformat_free_context(formatContext);

    return true;
}
