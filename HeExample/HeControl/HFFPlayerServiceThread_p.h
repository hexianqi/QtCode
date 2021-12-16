#pragma once

#include "HFFPlayerServiceThread.h"
#include <QtCore/QQueue>
#include <QtCore/QWaitCondition>
#include <QtCore/QMutexLocker>

HE_BEGIN_NAMESPACE

class HFFPlayerServiceThreadPrivate
{
public:
    HFFPlayerServiceThreadPrivate(HFFPlayerService *service);

public:
    volatile bool running = false;
    HFFPlayerService *service;
    QMutex mutex;
    QWaitCondition cond;
    QQueue<HFFPlayerServiceThread::Task> cache;
};

HE_END_NAMESPACE

