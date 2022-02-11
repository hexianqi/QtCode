/***************************************************************************************************
**      2019-10-24  HSpecElecThread
***************************************************************************************************/

#pragma once

#include "HAbstractThread.h"

HE_BEGIN_NAMESPACE

class HSpecElecThreadPrivate;

class HSpecElecThread : public HAbstractThread
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecElecThread)

public:
    explicit HSpecElecThread(QObject *parent = nullptr);
    ~HSpecElecThread() override;

public:
    QString typeName() override;

public:
    QString threadInfo() override;

protected:
    HSpecElecThread(HSpecElecThreadPrivate &p, QObject *parent = nullptr);

protected:
    bool handleAction(HActionType action) override;
    void handleData();

protected:
    virtual void init();
};

HE_END_NAMESPACE
