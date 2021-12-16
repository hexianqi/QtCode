/***************************************************************************************************
**      2020-07-28  HFFDecoderControl
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>

struct AVCodecContext;
struct AVRational;
struct AVFrame;
struct AVSubtitle;

HE_BEGIN_NAMESPACE

class HFFPacketQueue;
class HFFDecoderControlPrivate;

class HFFDecoderControl : public QObject
{
    Q_OBJECT

public:
    explicit HFFDecoderControl(QObject *parent = nullptr);
    ~HFFDecoderControl() override;

signals:
    void empty_packet_queue();

public:
    int pkt_serial();
    int finish_serial();

public:
    void set_start_pts(int64_t pts, AVRational tb);
    void set_finish();

public:
    void open(AVCodecContext *ctx);
    void close();
    int decode(HFFPacketQueue *packets, AVFrame *frame, AVSubtitle *sub);

protected:
    QScopedPointer<HFFDecoderControlPrivate> d_ptr;
};

HE_END_NAMESPACE

