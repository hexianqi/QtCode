/***************************************************************************************************
**      2018-06-19  HSlCodecDevice SL设备类（带编码）。
***************************************************************************************************/

#ifndef HSLCODECDEVICE_H
#define HSLCODECDEVICE_H

#include "HSlDevice.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HSlCodecDevicePrivate;

class HSlCodecDevice : public HSlDevice
{
    Q_DECLARE_PRIVATE(HSlCodecDevice)

public:
    explicit HSlCodecDevice();
    ~HSlCodecDevice() override;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

protected:
    HErrorType transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay = 0) override;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HSLCODECDEVICE_H
