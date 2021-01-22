/***************************************************************************************************
**      2020-06-02  HAbstractSimulateDevice 抽象模拟设备类。
***************************************************************************************************/

#pragma once

#include "HAbstractDevice.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HAbstractSimulateDevicePrivate;

class HAbstractSimulateDevice : public HAbstractDevice
{
    Q_DECLARE_PRIVATE(HAbstractSimulateDevice)

public:
    explicit HAbstractSimulateDevice();

public:
    bool open() override;
    bool close() override;

protected:
    HAbstractSimulateDevice(HAbstractSimulateDevicePrivate &);
};

HE_COMMUNICATE_END_NAMESPACE

