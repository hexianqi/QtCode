/***************************************************************************************************
**      2019-04-08  HSlDevice SL设备类。
***************************************************************************************************/

#pragma once

#include "HAbstractDevice.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HSlDevice1Private;

class HSlDevice1 : public HAbstractDevice
{
    Q_DECLARE_PRIVATE(HSlDevice1)

public:
    explicit HSlDevice1();
    ~HSlDevice1() override;

public:
    QString typeName() override;

public:
    HErrorType setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    HErrorType getData(HActionType action, QVector<uchar> &value, int delay = 0) override;

protected:
    HSlDevice1(HSlDevice1Private &);
};

HE_COMMUNICATE_END_NAMESPACE
