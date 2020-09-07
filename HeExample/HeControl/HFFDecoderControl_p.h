#pragma once

#include "HFFDecoderControl.h"
#include "HFFmpeg.h"

HE_CONTROL_BEGIN_NAMESPACE

class HFFDecoderControlPrivate
{
public:
    int reorder_pts = -1;           // let decoder reorder pts [0=off 1=on -1=auto]

public:
    AVCodecContext *codec_ctx = nullptr;
    AVPacket *pkt = nullptr;
    int pkt_serial = -1;
    bool pkt_pending = false;
    int finish_serial = -1;
    int64_t start_pts;
    AVRational start_pts_tb;
    int64_t next_pts;
    AVRational next_pts_tb;

};

HE_CONTROL_END_NAMESPACE

