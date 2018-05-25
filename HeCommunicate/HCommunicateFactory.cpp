#include "HCommunicateFactory_p.h"
#include "HSerialPort.h"
#include "HUsbPortCy.h"
#include "HDeviceCollection.h"
#include "HDeviceSL.h"
#include "HProtocol.h"
#include "HProtocolCollection.h"
#include "HeCore/HFactory.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

HCommunicateFactory::HCommunicateFactory()
    : d_ptr(new HCommunicateFactoryPrivate)
{
    registerClass();
}

HCommunicateFactory::HCommunicateFactory(HCommunicateFactoryPrivate &p)
    : d_ptr(&p)
{
    registerClass();
}

HCommunicateFactory::~HCommunicateFactory()
{
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
    Q_UNUSED(type)
    IProtocol *p = new HProtocol;
    p->initialize(param);
    return p;
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
    HFactory::registerClass<HDeviceSL>("HDeviceSL");
}

HE_COMMUNICATE_END_NAMESPACE
