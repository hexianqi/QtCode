/***************************************************************************************************
**      2019-04-03  HDelayThread    延时线程类。
***************************************************************************************************/

#pragma once

#include "HControllerGlobal.h"
#include "HeCore/HActionType.h"
#include <QtCore/QThread>

HE_CORE_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE

class IModel;
class HDelayThreadPrivate;

class HE_CONTROLLER_EXPORT HDelayThread : public QThread
{
    Q_OBJECT

public:
    explicit HDelayThread(IModel *parent);
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
