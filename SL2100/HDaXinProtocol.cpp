#include "HDaXinProtocol_p.h"
#include "HDaXinDevice.h"
#include "HeCommunicate/HSerialPort.h"

HDaXinProtocolPrivate::HDaXinProtocolPrivate()
{
    QVariantMap param;
    param.insert("timeOut", 1000);
    param.insert("baudRate", 38400);
    auto port = new HSerialPort();
    port->initialize(param);
    device = new HDaXinDevice;
    device->setPort(port, 4, true);
    device->addActionParam(ACT_SET_OUTPUT_VOLTAGE,     QList<uchar>() << 0x00 << 0x02 << 0x20);
    device->addActionParam(ACT_SET_OUTPUT_CURRENT,     QList<uchar>() << 0x00 << 0x02 << 0x21);
    device->addActionParam(ACT_SET_OVER_VOLTAGE,       QList<uchar>() << 0x00 << 0x02 << 0x22);
    device->addActionParam(ACT_SET_OVER_CURRENT,       QList<uchar>() << 0x00 << 0x02 << 0x23);
    device->addActionParam(ACT_SET_SOURCE_MODE,        QList<uchar>() << 0x00 << 0x02 << 0x24);
    device->addActionParam(ACT_SET_SOURCE_ADDR,        QList<uchar>() << 0x00 << 0x02 << 0x25);
    device->addActionParam(ACT_SET_SOURCE_OPERATION,   QList<uchar>() << 0x00 << 0x02 << 0x26);
    device->addActionParam(ACT_SET_SOURCE_FORWARD,     QList<uchar>() << 0x00 << 0x02 << 0x30);
    device->addActionParam(ACT_SET_SOURCE_REVERSE,     QList<uchar>() << 0x00 << 0x02 << 0x31);
    device->addActionParam(ACT_SET_SOURCE_IO,          QList<uchar>() << 0x00 << 0x02 << 0x32);
    device->addActionParam(ACT_GET_SOURCE_STATE,       QList<uchar>() << 0x00 << 0x01 << 0x27);
    device->addActionParam(ACT_GET_ELEC_DATA,          QList<uchar>() << 0x00 << 0x05 << 0x28);
}

HDaXinProtocol::HDaXinProtocol() :
    HBigProtocol(*new HDaXinProtocolPrivate)
{
}

HDaXinProtocol::HDaXinProtocol(HDaXinProtocolPrivate &p) :
    HBigProtocol(p)
{
}

HDaXinProtocol::~HDaXinProtocol() = default;

void HDaXinProtocol::initialize(QVariantMap param)
{
    Q_D(HDaXinProtocol);
    d->device->initialize(param);
}

QString HDaXinProtocol::typeName()
{
    return "HDaXinProtocol";
}
