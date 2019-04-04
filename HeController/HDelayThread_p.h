#ifndef HDELAYTHREAD_P_H
#define HDELAYTHREAD_P_H

#include "HDelayThread.h"
#include <QQueue>

class QMutex;
class QWaitCondition;

HE_CONTROLLER_BEGIN_NAMESPACE

class HDelayThreadPrivate
{
public:
    HDelayThreadPrivate(IModel *);

public:
    void enqueueAction(HActionType action, ulong delay);
    QPair<HActionType, ulong> dequeueAction();
    void clearAction();

public:
    IModel *model;
    QMutex *mutex;
    QWaitCondition *waitConditionAction;
    volatile bool running = false;
    QQueue<QPair<HActionType, ulong>> actionCache;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HDELAYTHREAD_P_H
