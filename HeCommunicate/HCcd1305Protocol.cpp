#include "HCcd1305Protocol_p.h"
#include "HUsbPortCy.h"
#include "HSlDevice2.h"
#include <QtCore/QDebug>

HE_COMMUNICATE_BEGIN_NAMESPACE

HCcd1305ProtocolPrivate::HCcd1305ProtocolPrivate()
{
    QVariantMap param;
    param.insert("timeOut", 5000);
    auto port = new HUsbPortCy;
    port->initialize(param);
    device = new HSlDevice2;
    device->setPort(port, 0, false);
    device->addActionParam(ACT_CHECK_DEVICE,        QList<uchar>() << 0x00 << 0x02 << 0x00);
    device->addActionParam(ACT_SET_INTEGRAL_TIME,   QList<uchar>() << 0x00 << 0x04 << 0x01);
    device->addActionParam(ACT_GET_SPECTRUM,        QList<uchar>() << 0x10 << 0x50 << 0x02);
    device->addActionParam(ACT_SET_RAM,             QList<uchar>() << 0xFF << 0xFA << 0x03);
    device->addActionParam(ACT_GET_RAM,             QList<uchar>() << 0xFF << 0xFA << 0x04);
}

HCcd1305Protocol::HCcd1305Protocol() :
    HBigProtocol(*new HCcd1305ProtocolPrivate)
{
}

HCcd1305Protocol::HCcd1305Protocol(HCcd1305ProtocolPrivate &p) :
    HBigProtocol(p)
{
}

HCcd1305Protocol::~HCcd1305Protocol()
{
    qDebug() << __func__;
}

void HCcd1305Protocol::initialize(QVariantMap param)
{
    Q_D(HCcd1305Protocol);
    d->device->initialize(param);
}

QString HCcd1305Protocol::typeName()
{
    return "HCcd1305Protocol";
}

HE_COMMUNICATE_END_NAMESPACE
