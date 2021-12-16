#pragma once

#include "HAbstractThread.h"
#include <QtCore/QQueue>
#include <QtCore/QSet>

class QMutex;
class QWaitCondition;

HE_BEGIN_NAMESPACE

class IProtocol;
class IActionStrategy;

class HE_CONTROLLER_EXPORT HAbstractThreadPrivate
{
public:
    HAbstractThreadPrivate();

public:
    void enqueueAction(HActionType action);
    HActionType dequeueAction();
    void clearAction();

public:
    QMutex *mutex;
    QWaitCondition *waitConditionAction;
    volatile bool running = false;
    QQueue<HActionType> actionCache;
    QSet<HActionType> actionSupport;
    QList<IProtocol *> protocols;
    QList<IActionStrategy *> strategys;
    int runMode = 2;    // 0:测试模式; 1:脱机模式; 2:联机模式;
    int retry = 3;
    uint sleepTime = 1000;
};

HE_END_NAMESPACE
