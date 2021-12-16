/***************************************************************************************************
**      2020-06-02  HSimulateDevice
***************************************************************************************************/

#pragma once

#include "HAbstractDevice.h"

HE_BEGIN_NAMESPACE

class HSimulateDevicePrivate;

class HSimulateDevice : public HAbstractDevice
{
    Q_DECLARE_PRIVATE(HSimulateDevice)

public:
    explicit HSimulateDevice();
    ~HSimulateDevice() override;

public:
    QString typeName() override;

public:
    bool open() override;
    bool close() override;

public:
    bool setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    bool getData(HActionType action, QVector<uchar> &value, int delay = 0) override;

protected:
    HSimulateDevice(HSimulateDevicePrivate &);

protected:
    uchar simulate(int value);
};

HE_END_NAMESPACE

