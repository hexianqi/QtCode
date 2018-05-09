#ifndef HABSTRACTTHREAD_P_H
#define HABSTRACTTHREAD_P_H

#include "HAbstractThread.h"
#include "HeCommunicate/HCommunicateGlobal.h"
#include <QQueue>

class QMutex;
class QWaitCondition;

HE_COMMUNICATE_BEGIN_NAMESPACE
class IProtocol;
HE_COMMUNICATE_END_NAMESPACE
HE_COMMUNICATE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class HAbstractThreadPrivate
{
    Q_DECLARE_PUBLIC(HAbstractThread)

public:
    HAbstractThreadPrivate();

public:
    void enqueueAction(HActionType action);
    HActionType dequeueAction();
    void clearAction();

public:
    HAbstractThread *q_ptr;
    IModel *model;
    QMutex *mutex;
    QWaitCondition *waitConditionAction;
    volatile bool running;
    QQueue<HActionType> actionQueue;
    QList<HActionType> actionSupport;
    int runMode = 2;    //0:测试模式; 1:脱机模式; 2:联机模式;
    int retry = 3;
    uint sleepTime = 1000;
    QMap<QString, IProtocol*> protocols;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HABSTRACTTHREAD_P_H
