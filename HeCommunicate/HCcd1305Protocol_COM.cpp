#include "HCcd1305Protocol_COM_p.h"
#include "HBigUCharConvert.h"
#include "HSerialPort.h"
#include "HSlDevice2.h"

HE_BEGIN_NAMESPACE

HCcd1305Protocol_COM::HCcd1305Protocol_COM(QObject *parent) :
    HAbstractProtocol(*new HCcd1305Protocol_COMPrivate, parent)
{
    init();
}

HCcd1305Protocol_COM::HCcd1305Protocol_COM(HCcd1305Protocol_COMPrivate &p, QObject *parent) :
    HAbstractProtocol(p, parent)
{
}

HCcd1305Protocol_COM::~HCcd1305Protocol_COM() = default;

QString HCcd1305Protocol_COM::typeName()
{
    return "HCcd1305Protocol_COM";
}

void HCcd1305Protocol_COM::init()
{
    Q_D(HCcd1305Protocol_COM);
    QVariantMap param;
    param.insert("timeOut", 3000);
    param.insert("baudRate", 115200);
    auto port = new HSerialPort;
    port->initialize(param);
    d->convert = new HBigUCharConvert(this);
    d->device = new HSlDevice2(this);
    d->device->setPort(port, 1, true);
    d->device->addActionParam(ACT_CHECK_DEVICE,        QList<uchar>() << 0x00 << 0x02 << 0x00);
    d->device->addActionParam(ACT_SET_INTEGRAL_TIME,   QList<uchar>() << 0x00 << 0x04 << 0x01);
    d->device->addActionParam(ACT_GET_SPECTRUM,        QList<uchar>() << 0x10 << 0x50 << 0x02);
    d->device->addActionParam(ACT_SET_RAM,             QList<uchar>() << 0xFF << 0xFA << 0x03);
    d->device->addActionParam(ACT_GET_RAM,             QList<uchar>() << 0xFF << 0xFA << 0x04);
}

HE_END_NAMESPACE
