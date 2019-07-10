#include "HCommunicateFactory_p.h"
#include "HSerialPort.h"
#include "HUsbPortCy.h"
#include "HDeviceCollection.h"
#include "HSlSimulation.h"
#include "HSlDevice.h"
#include "HSlDevice2.h"
#include "HSlCodecDevice.h"
#include "HDaXinDevice.h"
#include "HPowerFactorDevice.h"
#include "HLittleProtocol.h"
#include "HBigProtocol.h"
#include "HUi2008Protocol.h"
#include "HUi2010Protocol.h"
#include "HProtocolCollection.h"
#include "HeCore/HFactory.h"
#include <QtCore/QDebug>

HE_COMMUNICATE_BEGIN_NAMESPACE

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

HCommunicateFactory::~HCommunicateFactory()
{
    qDebug() << __func__;
}

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

IDeviceCollection *HCommunicateFactory::createDeviceCollection(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    IDeviceCollection *p = new HDeviceCollection;
    p->initialize(param);
    return p;
}

IProtocol *HCommunicateFactory::createProtocol(QString type, QVariantMap param)
{
    return HFactory::createObject<IProtocol>(type, param);
}

IProtocolCollection *HCommunicateFactory::createProtocolCollection(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    HProtocolCollection *p = new HProtocolCollection;
    p->initialize(param);
    return p;
}

void HCommunicateFactory::registerClass()
{
    HFactory::registerClass<HSerialPort>("HSerialPort");
    HFactory::registerClass<HUsbPortCy>("HUsbPortCy");
    HFactory::registerClass<HSlSimulation>("HSlSimulation");
    HFactory::registerClass<HSlDevice>("HSlDevice");
    HFactory::registerClass<HSlDevice2>("HSlDevice2");
    HFactory::registerClass<HSlCodecDevice>("HSlCodecDevice");
    HFactory::registerClass<HDaXinDevice>("HDaXinDevice");
    HFactory::registerClass<HPowerFactorDevice>("HPowerFactorDevice");
    HFactory::registerClass<HLittleProtocol>("HLittleProtocol");
    HFactory::registerClass<HBigProtocol>("HBigProtocol");
    HFactory::registerClass<HUi2008Protocol>("HUi2008Protocol");
    HFactory::registerClass<HUi2010Protocol>("HUi2010Protocol");
}

HE_COMMUNICATE_END_NAMESPACE
