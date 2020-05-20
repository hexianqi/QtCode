#include "HCcd554bProtocol_p.h"
#include "HUsbPortCy.h"
#include "HSlDevice.h"
#include <QtCore/QDebug>

HE_COMMUNICATE_BEGIN_NAMESPACE

HCcd554bProtocolPrivate::HCcd554bProtocolPrivate()
{
    QVariantMap param;
    param.insert("timeOut", 5000);
    auto port = new HUsbPortCy;
    port->initialize(param);
    device = new HSlDevice;
    device->setPort(port, 0, false);
    device->setDeviceID(0x81);
    device->addActionParam(ACT_CHECK_DEVICE,        QList<uchar>() << 0x00 << 0x02 << 0x03 << 0x00);
    device->addActionParam(ACT_SET_INTEGRAL_TIME,   QList<uchar>() << 0x00 << 0x04 << 0x03 << 0x05);
    device->addActionParam(ACT_GET_SPECTRUM,        QList<uchar>() << 0x12 << 0x00 << 0x03 << 0x11);
}

HCcd554bProtocol::HCcd554bProtocol() :
    HLittleProtocol(*new HCcd554bProtocolPrivate)
{
}

HCcd554bProtocol::HCcd554bProtocol(HCcd554bProtocolPrivate &p) :
    HLittleProtocol(p)
{
}

HCcd554bProtocol::~HCcd554bProtocol()
{
    qDebug() << __func__;
}

void HCcd554bProtocol::initialize(QVariantMap param)
{
    Q_D(HCcd554bProtocol);
    d->device->initialize(param);
}

QString HCcd554bProtocol::typeName()
{
    return "HCcd554bProtocol";
}

HE_COMMUNICATE_END_NAMESPACE
