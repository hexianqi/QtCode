/***************************************************************************************************
**      2019-04-03  HDelayThread    延时线程类。
***************************************************************************************************/

#ifndef HDELAYTHREAD_H
#define HDELAYTHREAD_H

#include "HControllerGlobal.h"
#include "HeCore/HActionType.h"
#include <QThread>

HE_CORE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class HDelayThreadPrivate;

class HDelayThread : public QThread
{
    Q_OBJECT

public:
    explicit HDelayThread(QObject *parent = nullptr);
    ~HDelayThread() override;

public:
    void stop();
    void addAction(HActionType action, ulong delay);
    void clearAction();

protected:
    void run() override;

protected:
    QScopedPointer<HDelayThreadPrivate> d_ptr;
};


HE_CONTROLLER_END_NAMESPACE

#endif // HDELAYTHREAD_H
