/***************************************************************************************************
**      2019-05-27  HDaXinDevice DaXin设备类。
***************************************************************************************************/

#ifndef HDAXINDEVICE_H
#define HDAXINDEVICE_H

#include "HAbstractDevice.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HDaXinDevicePrivate;

class HDaXinDevice : public HAbstractDevice
{
    Q_DECLARE_PRIVATE(HDaXinDevice)

public:
    explicit HDaXinDevice();
    ~HDaXinDevice() override;

public:
    QString typeName() override;

public:
    HErrorType setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    HErrorType getData(HActionType action, QVector<uchar> &value, int delay = 0) override;

protected:
    HErrorType check() override;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HDAXINDEVICE_H
