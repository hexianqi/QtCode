/***************************************************************************************************
**      2020-05-27  HIntegrateThread 光色电综合线程类。
***************************************************************************************************/

#pragma once

#include "HAbstractThread.h"

HE_BEGIN_NAMESPACE

class HIntegrateThreadPrivate;

class HE_CONTROLLER_EXPORT HIntegrateThread : public HAbstractThread
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HIntegrateThread)

public:
    explicit HIntegrateThread(QObject *parent = nullptr);
    ~HIntegrateThread() override;

public:
    QString typeName() override;

public:
    QString threadInfo() override;

protected:
    HIntegrateThread(HIntegrateThreadPrivate &p, QObject *parent = nullptr);

protected:
    bool handleAction(HActionType action) override;
    void handleData();

protected:
    virtual void init();
};

HE_END_NAMESPACE

