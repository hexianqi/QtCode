/***************************************************************************************************
**      2018-06-19  IThread 线程接口。
***************************************************************************************************/

#ifndef ITHREAD_H
#define ITHREAD_H

#include "HControllerGlobal.h"
#include "HeCore/IInitializeable.h"
#include "HeCore/HActionType.h"
#include <QtCore/QThread>

HE_CORE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class IThread : public QThread, public IInitializeable
{
    Q_OBJECT

public:
    using QThread::QThread;

signals:
    void startFailed(const QString &port, const QString &text);
    void startFinished();
    void stopFinished();
    void actionFailed(HActionType action, const QString &text);
    void actionFinished(HActionType action);

public:
    virtual QString threadInfo() = 0;

public:
    virtual void stop() = 0;
    virtual void addAction(HActionType action)= 0;
    virtual void clearAction() = 0;
};

HE_CONTROLLER_END_NAMESPACE

#endif // ITHREAD_H
