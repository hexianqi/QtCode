/***************************************************************************************************
**      2018-06-19  HAbstractDevice 抽象设备类。
***************************************************************************************************/

#ifndef HABSTRACTDEVICE_H
#define HABSTRACTDEVICE_H

#include "IDevice.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HAbstractDevicePrivate;

class HAbstractDevice : public IDevice
{
public:
    explicit HAbstractDevice();
    virtual ~HAbstractDevice();

public:
    void initialize(QVariantMap param) override;

public:
    bool isSupport(HActionType action) override;
    void setPort(IPort *port, int num = 0, bool scan = true) override;
    void setDeviceID(int value) override;
    void addActionParam(HActionType action, QList<uchar> value) override;

public:
    HErrorType open() override;
    HErrorType close() final;

protected:
    HAbstractDevice(HAbstractDevicePrivate &);

protected:
    virtual HErrorType open(int num);
    virtual HErrorType check();
    virtual HErrorType transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay = 0);

protected:
    QScopedPointer<HAbstractDevicePrivate> d_ptr;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HABSTRACTDEVICE_H
