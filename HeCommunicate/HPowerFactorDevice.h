/***************************************************************************************************
**      2019-05-27  HPowerFactorDevice 功率因数计。
***************************************************************************************************/

#pragma once

#include "HAbstractDevice.h"

HE_BEGIN_NAMESPACE

class HPowerFactorDevicePrivate;

class HPowerFactorDevice : public HAbstractDevice
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HPowerFactorDevice)

public:
    explicit HPowerFactorDevice(QObject *parent = nullptr);
    ~HPowerFactorDevice() override;

public:
    QString typeName() override;

public:
    bool setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    bool getData(HActionType action, QVector<uchar> &value, int delay = 0) override;
};

HE_END_NAMESPACE
