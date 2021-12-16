/***************************************************************************************************
**      2020-07-29  HFFDataControl
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QObject>

struct AVPacket;

HE_BEGIN_NAMESPACE

class HFFFrame;

class HFFClockPrivate;

class HFFClock : public QObject
{
    Q_OBJECT

public:
    explicit HFFClock(QObject *parent = nullptr);
    ~HFFClock() override;

public:
    double pts();
    double speed();
    double last_updated();

public:
    void init(int *queue_serial = nullptr);
    void set_paused(bool b);
    void set_clock(double pts, int serial);
    void set_clock(double pts, int serial, double time);
    void set_clock_speed(double speed);
    void sync_clock();
    void sync_clock(HFFClock *slave);
    double get_clock();

protected:
    QScopedPointer<HFFClockPrivate> d_ptr;
};

class HFFPacketQueuePrivate;

class HFFPacketQueue : public QObject
{
    Q_OBJECT

public:
    explicit HFFPacketQueue(QObject *parent = nullptr);
    ~HFFPacketQueue() override;

public:
    bool abort_request();
    int remaining();
    int *serial();
    int size();
    bool has_enough_packets(double tb);

public:
    void start();
    void abort();
    void flush();

public:
    bool put(AVPacket *pkt);
    int get(AVPacket *pkt, bool block, int *serial);

protected:
    QScopedPointer<HFFPacketQueuePrivate> d_ptr;

private:
    bool put_in(AVPacket *pkt);
};

class HFFFrameQueuePrivate;

class HFFFrameQueue : public QObject
{
    Q_OBJECT

public:
    explicit HFFFrameQueue(QObject *parent = nullptr);
    ~HFFFrameQueue() override;

public:
    int remaining();
    int rindex_shown();
    HFFFrame *peek();
    HFFFrame *peek_next();
    HFFFrame *peek_last();
    HFFFrame *peek_writeable();
    HFFFrame *peek_readable();

public:
    void init(int max_size, bool keep_last = false);
    void start();
    void abort();
    void flush();
    void push();
    void next();
    void wake();

protected:
    HFFFrame *peek(int i);
    void unref_item(HFFFrame *);

protected:
    QScopedPointer<HFFFrameQueuePrivate> d_ptr;
};

HE_END_NAMESPACE
