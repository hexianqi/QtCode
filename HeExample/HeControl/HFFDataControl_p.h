#pragma once

#include "HFFDataControl.h"
#include <QtCore/QVector>
#include <QtCore/QQueue>
#include <QtCore/QMutexLocker>
#include <QtCore/QWaitCondition>

HE_CONTROL_BEGIN_NAMESPACE

struct HFFPacket;

class HFFClockPrivate
{
public:
    double pts;           // clock base
    double pts_drift;     // clock base minus time at which we updated the clock
    double last_updated;
    double speed;
    int serial;           // clock is based on a packet with this serial
    bool paused;
    int *queue_serial;    // pointer to the current packet queue serial, used for obsolete clock detection
};

class HFFPacketQueuePrivate
{
public:
    bool abort_request = true;
    int serial = -1;
    int size = 0;
    int64_t duration = 0;

public:
    QMutex mutex;
    QWaitCondition cond;
    QQueue<HFFPacket *> cache;
};

class HFFFrameQueuePrivate
{
public:
    bool abort_request = true;
    bool keep_last = false;
    int rindex = 0;
    int rindex_shown = 0;
    int windex = 0;
    int size = 0;

public:
    QMutex mutex;
    QWaitCondition cond;
    QVector<HFFFrame *> cache;
};

HE_CONTROL_END_NAMESPACE

