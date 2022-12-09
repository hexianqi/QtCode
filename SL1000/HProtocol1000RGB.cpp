#include "HProtocol1000RGB_p.h"
#include "HeCommunicate/HSerialPort.h"
#include "HeCommunicate/HSlDevice3.h"

HProtocol1000RGBPrivate::HProtocol1000RGBPrivate()
{
    QVariantMap param;
    param.insert("timeOut", 3000);
    param.insert("baudRate", 115200);
    auto port = new HSerialPort;
    port->initialize(param);
    device = new HSlDevice3;
    device->setPort(port, 4, true);
    device->setDeviceID(0x01);
    device->addActionParam(ACT_CHECK_DEVICE,                QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x00);
    device->addActionParam(ACT_SET_SOURCE_MODE,             QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x05);
    device->addActionParam(ACT_SET_OUTPUT_VOLTAGE,          QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x06);
    device->addActionParam(ACT_SET_OUTPUT_CURRENT,          QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x07);
    device->addActionParam(ACT_SET_GEARS_OUTPUT_CURRENT,    QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x08);
    device->addActionParam(ACT_SET_GEARS_MEASURED_CURRENT,  QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x08);
    device->addActionParam(ACT_SET_REVERSE_VOLTAGE,         QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x09);
    device->addActionParam(ACT_SET_SOURCE_IO,               QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x0A);
    device->addActionParam(ACT_GET_ELEC_DATA,               QList<uchar>() << 0x00 << 0x18 << 0x01 << 0x11);
    device->addActionParam(ACT_GET_MEASURED_VOLTAGE,        QList<uchar>() << 0x00 << 0x08 << 0x01 << 0x12);
    device->addActionParam(ACT_GET_MEASURED_CURRENT,        QList<uchar>() << 0x00 << 0x08 << 0x01 << 0x13);
    device->addActionParam(ACT_GET_REVERSE_CURRENT,         QList<uchar>() << 0x00 << 0x08 << 0x01 << 0x14);
    device->addActionParam(ACT_SET_LUMINOUS_TYPE,           QList<uchar>() << 0x00 << 0x02 << 0x02 << 0x05);
    device->addActionParam(ACT_SET_LUMINOUS_GEARS,          QList<uchar>() << 0x00 << 0x02 << 0x02 << 0x06);
    device->addActionParam(ACT_GET_LUMINOUS_DATA,           QList<uchar>() << 0x00 << 0x02 << 0x02 << 0x11);
}

HProtocol1000RGB::HProtocol1000RGB() :
    HLittleProtocol(*new HProtocol1000RGBPrivate)
{
}

HProtocol1000RGB::~HProtocol1000RGB() = default;

void HProtocol1000RGB::initialize(QVariantMap param)
{
    Q_D(HProtocol1000RGB);
    d->device->initialize(param);
}

QString HProtocol1000RGB::typeName()
{
    return "HProtocol1000RGB";
}
