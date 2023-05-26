#include "HProtocol1000RGB_p.h"
#include "HeCommunicate/HLittleUCharConvert.h"
#include "HeCommunicate/HSerialPort.h"
#include "HeCommunicate/HSlDevice3.h"

HProtocol1000RGB::HProtocol1000RGB(QObject *parent) :
    HAbstractProtocol(*new HProtocol1000RGBPrivate, parent)
{
}

HProtocol1000RGB::~HProtocol1000RGB() = default;

QString HProtocol1000RGB::typeName()
{
    return "HProtocol1000RGB";
}

void HProtocol1000RGB::init()
{
    Q_D(HProtocol1000RGB);
    QVariantMap param;
    param.insert("timeOut", 3000);
    param.insert("baudRate", 115200);
    auto port = new HSerialPort(this);
    port->initialize(param);
    d->convert = new HLittleUCharConvert(this);
    d->device = new HSlDevice3(this);
    d->device->setPort(port, 4, true);
    d->device->setDeviceID(0x01);
    d->device->addActionParam(ACT_CHECK_DEVICE,                QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x00);
    d->device->addActionParam(ACT_SET_SOURCE_MODE,             QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x05);
    d->device->addActionParam(ACT_SET_OUTPUT_VOLTAGE,          QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x06);
    d->device->addActionParam(ACT_SET_OUTPUT_CURRENT,          QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x07);
    d->device->addActionParam(ACT_SET_GEARS_OUTPUT_CURRENT,    QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x08);
    d->device->addActionParam(ACT_SET_GEARS_MEASURED_CURRENT,  QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x08);
    d->device->addActionParam(ACT_SET_REVERSE_VOLTAGE,         QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x09);
    d->device->addActionParam(ACT_SET_SOURCE_IO,               QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x0A);
    d->device->addActionParam(ACT_GET_ELEC_DATA,               QList<uchar>() << 0x00 << 0x18 << 0x01 << 0x11);
    d->device->addActionParam(ACT_GET_MEASURED_VOLTAGE,        QList<uchar>() << 0x00 << 0x08 << 0x01 << 0x12);
    d->device->addActionParam(ACT_GET_MEASURED_CURRENT,        QList<uchar>() << 0x00 << 0x08 << 0x01 << 0x13);
    d->device->addActionParam(ACT_GET_REVERSE_CURRENT,         QList<uchar>() << 0x00 << 0x08 << 0x01 << 0x14);
    d->device->addActionParam(ACT_SET_LUMINOUS_TYPE,           QList<uchar>() << 0x00 << 0x02 << 0x02 << 0x05);
    d->device->addActionParam(ACT_SET_LUMINOUS_GEARS,          QList<uchar>() << 0x00 << 0x02 << 0x02 << 0x06);
    d->device->addActionParam(ACT_GET_LUMINOUS_DATA,           QList<uchar>() << 0x00 << 0x02 << 0x02 << 0x11);
}
