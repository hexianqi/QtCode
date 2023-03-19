#include "HCommunicateFactory_p.h"
#include "HSerialPort.h"
#include "HUsbPortCy.h"
#include "HSpecSimulateDevice.h"
#include "HSimulateDevice.h"
#include "HSlDevice1.h"
#include "HSlDevice2.h"
#include "HSlDevice3.h"
#include "HPowerFactorDevice.h"
#include "HLittleProtocol.h"
#include "HBigProtocol.h"
#include "HCcd1305Protocol.h"
#include "HCcd1305Protocol_COM.h"
#include "HCcd554bProtocol.h"
#include "HSl1000Protocol.h"
#include "HUi2008Protocol.h"
#include "HUi2010Protocol.h"
#include "HProtocolCollection.h"
#include "HeCore/HFactory.h"

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

IPort *HCommunicateFactory::createPort(QString type, QVariantMap param)
{
    return HFactory::createObject<IPort>(type, param);
}

IDevice *HCommunicateFactory::createDevice(QString type, QVariantMap param)
{
    return HFactory::createObject<IDevice>(type, param);
}

IProtocol *HCommunicateFactory::createProtocol(QString type, QVariantMap param)
{
    return HFactory::createObject<IProtocol>(type, param);
}

IProtocolCollection *HCommunicateFactory::createProtocolCollection(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    auto p = new HProtocolCollection;
    p->initialize(param);
    return p;
}

void HCommunicateFactory::registerClass()
{
    HFactory::registerClass<HSerialPort>("HSerialPort");
    HFactory::registerClass<HUsbPortCy>("HUsbPortCy");
    HFactory::registerClass<HSpecSimulateDevice>("HSpecSimulateDevice");
    HFactory::registerClass<HSimulateDevice>("HSimulateDevice");
    HFactory::registerClass<HSlDevice1>("HSlDevice1");
    HFactory::registerClass<HSlDevice2>("HSlDevice2");
    HFactory::registerClass<HSlDevice3>("HSlDevice3");
    HFactory::registerClass<HPowerFactorDevice>("HPowerFactorDevice");
    HFactory::registerClass<HLittleProtocol>("HLittleProtocol");
    HFactory::registerClass<HBigProtocol>("HBigProtocol");
    HFactory::registerClass<HCcd1305Protocol>("HCcd1305Protocol");
    HFactory::registerClass<HCcd1305Protocol_COM>("HCcd1305Protocol_COM");
    HFactory::registerClass<HCcd554bProtocol>("HCcd554bProtocol");
    HFactory::registerClass<HCcd1305Protocol>("HCcdProtocol01");
    HFactory::registerClass<HCcd1305Protocol_COM>("HCcdProtocol11");
    HFactory::registerClass<HCcd554bProtocol>("HCcdProtocol02");
    HFactory::registerClass<HSl1000Protocol>("HSl1000Protocol");
    HFactory::registerClass<HUi2008Protocol>("HUi2008Protocol");
    HFactory::registerClass<HUi2010Protocol>("HUi2010Protocol");
}

HE_END_NAMESPACE
