#include "HCommunicateFactory_p.h"
#include "HBigUCharConvert.h"
#include "HLittleUCharConvert.h"
#include "HSerialPort.h"
#include "HUsbPortCy.h"
#include "HSpecSimulateDevice.h"
#include "HSimulateDevice.h"
#include "HSlDevice1.h"
#include "HSlDevice2.h"
#include "HSlDevice3.h"
#include "HPowerFactorDevice.h"
#include "HProtocol.h"
#include "HCcd1305Protocol.h"
#include "HCcd1305Protocol_COM.h"
#include "HCcd554bProtocol.h"
#include "HSl1000Protocol.h"
#include "HUi2008Protocol.h"
#include "HUi2010Protocol.h"
#include "HProtocolCollection.h"
#include "HeCore/HObjectFactory.h"

HE_BEGIN_NAMESPACE

HCommunicateFactory::HCommunicateFactory(QObject *parent) :
    QObject(parent),
    d_ptr(new HCommunicateFactoryPrivate)
{
    registerClass();
}

HCommunicateFactory::HCommunicateFactory(HCommunicateFactoryPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
    registerClass();
}

HCommunicateFactory::~HCommunicateFactory() = default;

void HCommunicateFactory::initialize(QVariantMap /*param*/)
{
}

QString HCommunicateFactory::typeName()
{
    return "HCommunicateFactory";
}

IUCharConvert *HCommunicateFactory::createUCharConvert(QString type, QObject *parent, QVariantMap param)
{
    if (parent == nullptr)
        parent = this;
    return HObjectFactory::createObject<IUCharConvert>(type, param, parent);
}

IPort *HCommunicateFactory::createPort(QString type, QObject *parent, QVariantMap param)
{
    if (parent == nullptr)
        parent = this;
    return HObjectFactory::createObject<IPort>(type, param, parent);
}

IDevice *HCommunicateFactory::createDevice(QString type, QObject *parent, QVariantMap param)
{
    if (parent == nullptr)
        parent = this;
    return HObjectFactory::createObject<IDevice>(type, param, parent);
}

IProtocol *HCommunicateFactory::createProtocol(QString type, QObject *parent, QVariantMap param)
{
    if (parent == nullptr)
        parent = this;
    return HObjectFactory::createObject<IProtocol>(type, param, parent);
}

IProtocolCollection *HCommunicateFactory::createProtocolCollection(QString /*type*/, QVariantMap param)
{
    auto p = new HProtocolCollection;
    p->initialize(param);
    return p;
}

void HCommunicateFactory::registerClass()
{
    HObjectFactory::registerClass<HBigUCharConvert>("HBigUCharConvert");
    HObjectFactory::registerClass<HLittleUCharConvert>("HLittleUCharConvert");
    HObjectFactory::registerClass<HSerialPort>("HSerialPort");
    HObjectFactory::registerClass<HUsbPortCy>("HUsbPortCy");
    HObjectFactory::registerClass<HSpecSimulateDevice>("HSpecSimulateDevice");
    HObjectFactory::registerClass<HSimulateDevice>("HSimulateDevice");
    HObjectFactory::registerClass<HSlDevice1>("HSlDevice1");
    HObjectFactory::registerClass<HSlDevice2>("HSlDevice2");
    HObjectFactory::registerClass<HSlDevice3>("HSlDevice3");
    HObjectFactory::registerClass<HPowerFactorDevice>("HPowerFactorDevice");
    HObjectFactory::registerClass<HProtocol>("HProtocol");
    HObjectFactory::registerClass<HCcd1305Protocol>("HCcd1305Protocol");
    HObjectFactory::registerClass<HCcd1305Protocol_COM>("HCcd1305Protocol_COM");
    HObjectFactory::registerClass<HCcd554bProtocol>("HCcd554bProtocol");
    HObjectFactory::registerClass<HCcd1305Protocol>("HCcdProtocol01");
    HObjectFactory::registerClass<HCcd1305Protocol_COM>("HCcdProtocol11");
    HObjectFactory::registerClass<HCcd554bProtocol>("HCcdProtocol02");
    HObjectFactory::registerClass<HSl1000Protocol>("HSl1000Protocol");
    HObjectFactory::registerClass<HUi2008Protocol>("HUi2008Protocol");
    HObjectFactory::registerClass<HUi2010Protocol>("HUi2010Protocol");
}

HE_END_NAMESPACE
