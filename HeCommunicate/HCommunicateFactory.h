/***************************************************************************************************
**      2018-06-19  HCommunicateFactory 通讯器工厂类。
***************************************************************************************************/

#pragma once

#include "ICommunicateFactory.h"

HE_BEGIN_NAMESPACE

class HCommunicateFactoryPrivate;

class HCommunicateFactory : public QObject, public ICommunicateFactory
{
    Q_OBJECT

public:
    explicit HCommunicateFactory(QObject *parent = nullptr);
    ~HCommunicateFactory() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

public:
    IUCharConvert *createUCharConvert(QString type, QObject *parent = nullptr, QVariantMap param = QVariantMap()) override;
    IPort *createPort(QString type, QObject *parent = nullptr, QVariantMap param = QVariantMap()) override;
    IDevice *createDevice(QString type, QObject *parent = nullptr, QVariantMap param = QVariantMap()) override;
    IProtocol *createProtocol(QString type, QObject *parent = nullptr, QVariantMap param = QVariantMap()) override;
    IProtocolCollection *createProtocolCollection(QString type, QVariantMap param = QVariantMap()) override;

protected:
    HCommunicateFactory(HCommunicateFactoryPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HCommunicateFactoryPrivate> d_ptr;

private:
    void registerClass();
};

HE_END_NAMESPACE
