/***************************************************************************************************
**      2022-03-15  HKeyenceDevice
***************************************************************************************************/

#pragma once

#include "HeCommunicate/HAbstractDevice.h"

HE_USE_NAMESPACE

class HKeyenceDevicePrivate;

class HKeyenceDevice : public HAbstractDevice
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HKeyenceDevice)

public:
    explicit HKeyenceDevice(QObject *parent = nullptr);
    ~HKeyenceDevice() override;

public:
    QString typeName() override;

public:
    bool setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    bool getData(HActionType action, QVector<uchar> &value, int delay = 0) override;

protected:
    bool checkDevice() override;
};
