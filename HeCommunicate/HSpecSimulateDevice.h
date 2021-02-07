/***************************************************************************************************
**      2020-06-02  HSpecSimulateDevice 模拟光谱仪类。
***************************************************************************************************/

#pragma once

#include "HAbstractDevice.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HSpecSimulateDevicePrivate;

class HSpecSimulateDevice : public HAbstractDevice
{
    Q_DECLARE_PRIVATE(HSpecSimulateDevice)

public:
    explicit HSpecSimulateDevice();
    ~HSpecSimulateDevice() override;

public:
    QString typeName() override;

public:
    bool open() override;
    bool close() override;

public:
    bool setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    bool getData(HActionType action, QVector<uchar> &value, int delay = 0) override;

protected:
    HSpecSimulateDevice(HSpecSimulateDevicePrivate &);

protected:
    double simulate(double value);
};

HE_COMMUNICATE_END_NAMESPACE

