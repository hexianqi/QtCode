#include "HCommunicateFactory_p.h"
#include "HSerialPort.h"
#include "HUsbPortCy.h"
#include "HDeviceCollection.h"
#include "HDeviceSL.h"
#include "HProtocol.h"
#include "HProtocolCollection.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

HCommunicateFactory::HCommunicateFactory()
    : d_ptr(new HCommunicateFactoryPrivate)
{
}

HCommunicateFactory::HCommunicateFactory(HCommunicateFactoryPrivate &p)
    : d_ptr(&p)
{
}

HCommunicateFactory::~HCommunicateFactory()
{
}

void HCommunicateFactory::initialize(QVariantMap param)
{
    Q_UNUSED(param)
}

IPort *HCommunicateFactory::createPort(QString type, QVariantMap param)
{
    IPort *p = nullptr;
    if (type.compare("COM", Qt::CaseInsensitive) == 0)
        p = new HSerialPort;
    if (type.compare("USB_Cy", Qt::CaseInsensitive) == 0)
        p = new HUsbPortCy;
    if (p != nullptr)
        p->initialize(param);
    return p;
}

IDevice *HCommunicateFactory::createDevice(QString type, QVariantMap param)
{
    IDevice *p = nullptr;
    if (type.compare("SL", Qt::CaseInsensitive) == 0)
        p = new HDeviceSL;
    if (p != nullptr)
        p->initialize(param);
    return p;
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

HE_COMMUNICATE_END_NAMESPACE
