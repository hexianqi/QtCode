#pragma once

#include "HNamespace.h"
extern "C" {
#include "libavcodec/avcodec.h"
}

HE_BEGIN_NAMESPACE

struct HFFAudioParams
{
    int freq;
    int channels;
    int64_t channel_layout;
    AVSampleFormat format;
    int frame_size;
    int bytes_per_sec;
};

// Common struct for handling all types of decoded data and allocated render buffers.
struct HFFFrame
{
    AVFrame *frame;
    AVSubtitle sub;
    int serial;
    double pts;           // presentation timestamp for the frame
    double duration;      // estimated duration of the frame
    int64_t pos;          // byte position of the frame in the input file
    int width;
    int height;
    int format;
    AVRational sar;
    bool uploaded;
    int flip_v;
};

struct HFFPacket
{
    AVPacket pkt;
    int serial;
};

HE_END_NAMESPACE
