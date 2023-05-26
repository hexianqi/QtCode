/***************************************************************************************************
**      2020-06-02  HSpecSimulateDevice 模拟光谱仪类。
***************************************************************************************************/

#pragma once

#include "HAbstractDevice.h"

HE_BEGIN_NAMESPACE

class HSpecSimulateDevicePrivate;

class HSpecSimulateDevice : public HAbstractDevice
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecSimulateDevice)

public:
    explicit HSpecSimulateDevice(QObject *parent = nullptr);
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
    HSpecSimulateDevice(HSpecSimulateDevicePrivate &, QObject *parent = nullptr);

protected:
    double simulate(double value);
    uchar simulate(int value);
};

HE_END_NAMESPACE

