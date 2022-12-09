/***************************************************************************************************
**      2022-12-06  HThread1000RGB
***************************************************************************************************/

#pragma once

#include "HeController/HAbstractThread.h"

HE_USE_NAMESPACE

class HThread1000RGBPrivate;

class HThread1000RGB : public HAbstractThread
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HThread1000RGB)

public:
    explicit HThread1000RGB(QObject *parent = nullptr);
    ~HThread1000RGB() override;

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



