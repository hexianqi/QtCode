#ifndef ITHREAD_H
#define ITHREAD_H

#include "HControllerGlobal.h"
#include "HeCore/HActionType.h"
#include <QThread>
#include <QVariant>

HE_CORE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class HE_CONTROLLER_EXPORT IThread : public QThread
{
public:
    using QThread::QThread;

public:
    virtual void initialize(QVariantMap param) = 0;
    virtual QString threadInfo() = 0;

public:
    virtual void stop() = 0;
    virtual void addAction(HActionType action)= 0;
    virtual void clearAction() = 0;
};

HE_CONTROLLER_END_NAMESPACE

#endif // ITHREAD_H
