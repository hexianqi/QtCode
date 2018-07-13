/***************************************************************************************************
**      2018-06-19  HCommunicateFactory 通讯器工厂类。
***************************************************************************************************/

#ifndef HCOMMUNICATEFACTORY_H
#define HCOMMUNICATEFACTORY_H

#include "ICommunicateFactory.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HCommunicateFactoryPrivate;

class HCommunicateFactory : public QObject, public ICommunicateFactory
{
    Q_OBJECT

public:
    explicit HCommunicateFactory(QObject *parent = nullptr);
    ~HCommunicateFactory();

public:
    virtual void initialize(QVariantMap param) override;
    virtual QString typeName() override;

public:
    virtual IPort *createPort(QString type, QVariantMap param = QVariantMap()) override;
    virtual IDevice *createDevice(QString type, QVariantMap param = QVariantMap()) override;
    virtual IDeviceCollection *createDeviceCollection(QString type, QVariantMap param = QVariantMap()) override;
    virtual IProtocol *createProtocol(QString type, QVariantMap param = QVariantMap()) override;
    virtual IProtocolCollection *createProtocolCollection(QString type, QVariantMap param = QVariantMap()) override;

protected:
    HCommunicateFactory(HCommunicateFactoryPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HCommunicateFactoryPrivate> d_ptr;

private:
    void registerClass();
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HCOMMUNICATEFACTORY_H
