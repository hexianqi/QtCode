#pragma once

#include "HAbstractThread.h"
#include <QtCore/QQueue>
#include <QtCore/QSet>

class QMutex;
class QWaitCondition;

HE_BEGIN_NAMESPACE

class IProtocol;
class IActionStrategy;
class ITestData;

class HE_CONTROLLER_EXPORT HAbstractThreadPrivate
{
public:
    HAbstractThreadPrivate();

public:
    void enqueueAction(HActionType action);
    HActionType dequeueAction();
    void clearAction();

public:
    volatile bool running = false;
    QMutex *mutex;
    QWaitCondition *waitConditionAction;
    QQueue<HActionType> actionCache;
    QSet<HActionType> actionSupport;
    QList<IProtocol *> protocols;
    QList<IActionStrategy *> strategys;
    int retry = 3;
    uint sleepTime = 1000;

public:
    ITestData *testData = nullptr;
};

HE_END_NAMESPACE
