/***************************************************************************************************
**      2020-06-02  HSlSimulateDevice
***************************************************************************************************/

#pragma once

#include "HAbstractSimulateDevice.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HSlSimulateDevicePrivate;

class HSlSimulateDevice : public HAbstractSimulateDevice
{
    Q_DECLARE_PRIVATE(HSlSimulateDevice)

public:
    explicit HSlSimulateDevice();
    ~HSlSimulateDevice() override;

public:
    QString typeName() override;

public:
    HErrorType setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    HErrorType getData(HActionType action, QVector<uchar> &value, int delay = 0) override;

protected:
    HSlSimulateDevice(HSlSimulateDevicePrivate &);

protected:
    uchar simulate(int value);
};

HE_COMMUNICATE_END_NAMESPACE

