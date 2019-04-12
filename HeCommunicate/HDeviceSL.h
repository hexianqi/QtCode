/***************************************************************************************************
**      2019-04-08  HDeviceSL SL设备类。
***************************************************************************************************/

#ifndef HDEVICESL_H
#define HDEVICESL_H

#include "HAbstractDevice.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HDeviceSLPrivate;

class HDeviceSL : public HAbstractDevice
{
    Q_DECLARE_PRIVATE(HDeviceSL)

public:
    explicit HDeviceSL();
    ~HDeviceSL() override;

public:
    QString typeName() override;

public:
    HErrorType setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    HErrorType getData(HActionType action, QVector<uchar> &value, int delay = 0) override;

protected:
    HDeviceSL(HDeviceSLPrivate &);

protected:
    virtual HErrorType transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay = 0);
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HDEVICESL_H
