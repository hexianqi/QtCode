#include "HCommunicateFactory.h"
#include "HSerialPort.h"
#include "HUsbPortCy.h"
#include "HDeviceSL.h"
#include "HProtocol.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

HCommunicateFactory::HCommunicateFactory(QObject *parent)
    : QObject(parent)
{
}

void HCommunicateFactory::initialize(QVariantMap param)
{
    Q_UNUSED(param)
}

IPort *HCommunicateFactory::createPort(QString type, QVariantMap param)
{
    IPort *port = nullptr;
    if (type.compare("COM", Qt::CaseInsensitive) == 0)
        port = new HSerialPort(this);
    if (type.compare("USB_Cy", Qt::CaseInsensitive) == 0)
        port = new HUsbPortCy(this);
    if (port != nullptr)
        port->initialize(param);
    return port;
}

IDevice *HCommunicateFactory::createDevice(QString type, QVariantMap param)
{
    IDevice *device = nullptr;
    if (type.compare("SL", Qt::CaseInsensitive) == 0)
        device = new HDeviceSL(this);
    if (device != nullptr)
        device->initialize(param);
    return device;
}

IProtocol *HCommunicateFactory::createProtocol(QString type, QVariantMap param)
{
    Q_UNUSED(type)
    IProtocol *protocol = new HProtocol(this);
    protocol->initialize(param);
    return protocol;
}

HE_COMMUNICATE_END_NAMESPACE
