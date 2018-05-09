#ifndef HABSTRACTDEVICE_H
#define HABSTRACTDEVICE_H

#include "IDevice.h"
#include <QScopedPointer>

HE_COMMUNICATE_BEGIN_NAMESPACE

class HAbstractDevicePrivate;

class HAbstractDevice : public QObject, public IDevice
{
    Q_OBJECT

public:
    explicit HAbstractDevice(QObject *parent = nullptr);
    virtual ~HAbstractDevice();

public:
    virtual void initialize(QVariantMap param) override;
    virtual void setPort(IPort *port, int num = 0, bool scan = true) override;
    virtual void setDeviceID(int id) override;
    virtual void addActionParam(HActionType key, QList<uchar> value) override;

public:
    virtual HErrorType open() override;
    virtual HErrorType close() override;

protected:
    HAbstractDevice(HAbstractDevicePrivate &p, QObject *parent = nullptr);

protected:
    virtual HErrorType open(int num);
    virtual HErrorType check();

protected:
    QScopedPointer<HAbstractDevicePrivate> d_ptr;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HABSTRACTDEVICE_H
