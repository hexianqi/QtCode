/***************************************************************************************************
**      2021-04-07  HThread2100AC
***************************************************************************************************/

#pragma once

#include "HeController/HAbstractThread.h"

HE_CONTROLLER_USE_NAMESPACE

class HThread2000ACPrivate;

class HThread2000AC : public HAbstractThread
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HThread2000AC)

public:
    explicit HThread2000AC(QObject *parent = nullptr);
    ~HThread2000AC() override;

public:
    QString typeName() override;

public:
    QString threadInfo() override;

protected:
    bool handleAction(HActionType action) override;

private:
    void init();
};
