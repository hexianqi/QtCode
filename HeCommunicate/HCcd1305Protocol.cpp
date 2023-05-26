#include "HCcd1305Protocol_p.h"
#include "HBigUCharConvert.h"
#include "HUsbPortCy.h"
#include "HSlDevice2.h"

HE_BEGIN_NAMESPACE

HCcd1305Protocol::HCcd1305Protocol(QObject *parent) :
    HAbstractProtocol(*new HCcd1305ProtocolPrivate, parent)
{
    init();
}

HCcd1305Protocol::HCcd1305Protocol(HCcd1305ProtocolPrivate &p, QObject *parent) :
    HAbstractProtocol(p, parent)
{
}

HCcd1305Protocol::~HCcd1305Protocol() = default;

QString HCcd1305Protocol::typeName()
{
    return "HCcd1305Protocol";
}

void HCcd1305Protocol::init()
{
    Q_D(HCcd1305Protocol);
    QVariantMap param;
    param.insert("timeOut", 5000);
    auto port = new HUsbPortCy(this);
    port->initialize(param);
    d->convert = new HBigUCharConvert(this);
    d->device = new HSlDevice2(this);
    d->device->setPort(port, 0, false);
    d->device->addActionParam(ACT_CHECK_DEVICE,        QList<uchar>() << 0x00 << 0x02 << 0x00);
    d->device->addActionParam(ACT_SET_INTEGRAL_TIME,   QList<uchar>() << 0x00 << 0x04 << 0x01);
    d->device->addActionParam(ACT_GET_SPECTRUM,        QList<uchar>() << 0x10 << 0x50 << 0x02);
    d->device->addActionParam(ACT_SET_RAM,             QList<uchar>() << 0xFF << 0xFA << 0x03);
    d->device->addActionParam(ACT_GET_RAM,             QList<uchar>() << 0xFF << 0xFA << 0x04);
}

HE_END_NAMESPACE
