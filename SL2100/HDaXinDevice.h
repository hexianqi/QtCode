/***************************************************************************************************
**      2019-05-27  HDaXinDevice DaXin设备类。
***************************************************************************************************/

#pragma once

#include "HeCommunicate/HAbstractDevice.h"

HE_USE_NAMESPACE

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
    bool setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    bool getData(HActionType action, QVector<uchar> &value, int delay = 0) override;

protected:
    bool check() override;
};
