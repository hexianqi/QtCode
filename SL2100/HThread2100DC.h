/***************************************************************************************************
**      2021-01-20  HThread2100DC
***************************************************************************************************/

#pragma once

#include "HeController/HAbstractThread.h"

HE_USE_NAMESPACE

class HThread2100DCPrivate;

class HThread2100DC : public HAbstractThread
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HThread2100DC)

public:
    explicit HThread2100DC(QObject *parent = nullptr);
    ~HThread2100DC() override;

public:
    QString typeName() override;

public:
    QString threadInfo() override;

protected:
    bool handleAction(HActionType action) override;
    void handleData();

protected:
    virtual void init();
};



