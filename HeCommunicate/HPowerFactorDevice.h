/***************************************************************************************************
**      2019-05-27  HPowerFactorDevice 功率因素计。
***************************************************************************************************/

#ifndef HPOWERFACTORDEVICE_H
#define HPOWERFACTORDEVICE_H

#include "HAbstractDevice.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HPowerFactorDevicePrivate;

class HPowerFactorDevice : public HAbstractDevice
{
    Q_DECLARE_PRIVATE(HPowerFactorDevice)

public:
    explicit HPowerFactorDevice();
    ~HPowerFactorDevice() override;

public:
    QString typeName() override;

public:
    HErrorType setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    HErrorType getData(HActionType action, QVector<uchar> &value, int delay = 0) override;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HPOWERFACTORDEVICE_H
