#ifndef HCOMMUNICATEFACTORY_H
#define HCOMMUNICATEFACTORY_H

#include "ICommunicateFactory.h"
#include <QObject>

HE_COMMUNICATE_BEGIN_NAMESPACE

class HCommunicateFactory : public QObject, public ICommunicateFactory
{
    Q_OBJECT

public:
    explicit HCommunicateFactory(QObject *parent = nullptr);

public:
    virtual void initialize(QVariantMap param) override;
    virtual IPort *createPort(QString type, QVariantMap param = QVariantMap()) override;
    virtual IDevice *createDevice(QString type, QVariantMap param = QVariantMap()) override;
    virtual IProtocol *createProtocol(QString type, QVariantMap param = QVariantMap()) override;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HCOMMUNICATEFACTORY_H
