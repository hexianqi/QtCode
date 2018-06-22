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
    virtual void initialize(QVariantMap param) override;
    virtual bool isSupport(HActionType action) override;
    virtual void setPort(IPort *port, int num = 0, bool scan = true) override;
    virtual void setDeviceID(int id) override;
    virtual void addActionParam(HActionType action, QList<uchar> value) override;

public:
    virtual HErrorType open() override;
    virtual HErrorType close() override;

protected:
    HAbstractDevice(HAbstractDevicePrivate &p);

protected:
    virtual HErrorType open(int num);
    virtual HErrorType check();

protected:
    QScopedPointer<HAbstractDevicePrivate> d_ptr;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HABSTRACTDEVICE_H
