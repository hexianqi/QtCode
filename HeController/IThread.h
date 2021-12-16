/***************************************************************************************************
**      2018-06-19  IThread 线程接口。
***************************************************************************************************/

#pragma once

#include "HControllerGlobal.h"
#include "HeCore/IInitializeable.h"
#include "HeCore/HActionType.h"
#include <QtCore/QThread>

HE_BEGIN_NAMESPACE

class HE_CONTROLLER_EXPORT IThread : public QThread, public IInitializeable
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

HE_END_NAMESPACE
