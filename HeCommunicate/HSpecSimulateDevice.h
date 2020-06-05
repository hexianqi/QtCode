/***************************************************************************************************
**      2020-06-02  HSpecSimulateDevice 模拟光谱仪类。
***************************************************************************************************/

#pragma once

#include "HAbstractSimulateDevice.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HSpecSimulateDevicePrivate;

class HSpecSimulateDevice : public HAbstractSimulateDevice
{
    Q_DECLARE_PRIVATE(HSpecSimulateDevice)

public:
    explicit HSpecSimulateDevice();
    ~HSpecSimulateDevice() override;

public:
    QString typeName() override;

public:
    HErrorType setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    HErrorType getData(HActionType action, QVector<uchar> &value, int delay = 0) override;

protected:
    HSpecSimulateDevice(HSpecSimulateDevicePrivate &);

protected:
    double simulate(double value);
};

HE_COMMUNICATE_END_NAMESPACE

