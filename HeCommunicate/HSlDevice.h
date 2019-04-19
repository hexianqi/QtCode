/***************************************************************************************************
**      2019-04-08  HSlDevice SL设备类。
***************************************************************************************************/

#ifndef HSLDEVICE_H
#define HSLDEVICE_H

#include "HAbstractDevice.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HSlDevicePrivate;

class HSlDevice : public HAbstractDevice
{
    Q_DECLARE_PRIVATE(HSlDevice)

public:
    explicit HSlDevice();
    ~HSlDevice() override;

public:
    QString typeName() override;

public:
    HErrorType setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    HErrorType getData(HActionType action, QVector<uchar> &value, int delay = 0) override;

protected:
    HSlDevice(HSlDevicePrivate &);

protected:
    virtual HErrorType transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay = 0);
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HSLDEVICE_H
