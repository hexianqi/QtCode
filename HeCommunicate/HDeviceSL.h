/***************************************************************************************************
**      2018-06-19  HDeviceSL SL设备类。
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
    ~HDeviceSL();

public:
    virtual void initialize(QVariantMap param) override;
    virtual QString typeName() override;

public:
    virtual HErrorType setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    virtual HErrorType getData(HActionType action, QVector<uchar> &value, int delay = 0) override;

public:
    virtual void setEncrypt(QVector<bool> value);
    virtual void setCheckCode(QVector<bool> value);

protected:
    HDeviceSL(HDeviceSLPrivate &p);

protected:
    virtual HErrorType transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay = 0);
    virtual QVector<uchar> encrypt(QVector<uchar> value);
    virtual QVector<uchar> decrypt(QVector<uchar> value);
    virtual int calcEncryptSize(QVector<uchar> value);
    virtual uchar calcCode(QVector<uchar> value);
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HDEVICESL_H
