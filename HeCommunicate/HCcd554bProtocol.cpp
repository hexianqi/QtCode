#include "HCcd554bProtocol_p.h"
#include "HLittleUCharConvert.h"
#include "HUsbPortCy.h"
#include "HSlDevice1.h"

HE_BEGIN_NAMESPACE

HCcd554bProtocol::HCcd554bProtocol(QObject *parent) :
    HAbstractProtocol(*new HCcd554bProtocolPrivate, parent)
{
    init();
}

HCcd554bProtocol::HCcd554bProtocol(HCcd554bProtocolPrivate &p, QObject *parent) :
    HAbstractProtocol(p, parent)
{
}

HCcd554bProtocol::~HCcd554bProtocol() = default;


QString HCcd554bProtocol::typeName()
{
    return "HCcd554bProtocol";
}

void HCcd554bProtocol::init()
{
    Q_D(HCcd554bProtocol);
    QVariantMap param;
    param.insert("timeOut", 5000);
    auto port = new HUsbPortCy(this);
    port->initialize(param);
    d->convert = new HLittleUCharConvert(this);
    d->device = new HSlDevice1(this);
    d->device->setPort(port, 0, false);
    d->device->setDeviceID(0x81);
    d->device->addActionParam(ACT_CHECK_DEVICE,        QList<uchar>() << 0x00 << 0x02 << 0x03 << 0x00);
    d->device->addActionParam(ACT_SET_INTEGRAL_TIME,   QList<uchar>() << 0x00 << 0x04 << 0x03 << 0x05);
    d->device->addActionParam(ACT_GET_SPECTRUM,        QList<uchar>() << 0x12 << 0x00 << 0x03 << 0x11);
}


HE_END_NAMESPACE
