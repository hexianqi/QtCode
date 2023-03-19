#include "HCcd1305Protocol_COM_p.h"
#include "HSerialPort.h"
#include "HSlDevice2.h"

HE_BEGIN_NAMESPACE

HCcd1305Protocol_COMPrivate::HCcd1305Protocol_COMPrivate()
{
    QVariantMap param;
    param.insert("timeOut", 3000);
    param.insert("baudRate", 115200);
    auto port = new HSerialPort;
    port->initialize(param);
    device = new HSlDevice2;
    device->setPort(port, 5, true);
    device->addActionParam(ACT_CHECK_DEVICE,        QList<uchar>() << 0x00 << 0x02 << 0x00);
    device->addActionParam(ACT_SET_INTEGRAL_TIME,   QList<uchar>() << 0x00 << 0x04 << 0x01);
    device->addActionParam(ACT_GET_SPECTRUM,        QList<uchar>() << 0x10 << 0x50 << 0x02);
    device->addActionParam(ACT_SET_RAM,             QList<uchar>() << 0xFF << 0xFA << 0x03);
    device->addActionParam(ACT_GET_RAM,             QList<uchar>() << 0xFF << 0xFA << 0x04);
}

HCcd1305Protocol_COM::HCcd1305Protocol_COM() :
    HBigProtocol(*new HCcd1305Protocol_COMPrivate)
{
}

HCcd1305Protocol_COM::HCcd1305Protocol_COM(HCcd1305Protocol_COMPrivate &p) :
    HBigProtocol(p)
{
}

HCcd1305Protocol_COM::~HCcd1305Protocol_COM() = default;

void HCcd1305Protocol_COM::initialize(QVariantMap param)
{
    Q_D(HCcd1305Protocol_COM);
    d->device->initialize(param);
}

QString HCcd1305Protocol_COM::typeName()
{
    return "HCcd1305Protocol_COM";
}

HE_END_NAMESPACE
