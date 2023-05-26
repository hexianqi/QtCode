#include "HDaXinProtocol_p.h"
#include "HDaXinDevice.h"
#include "HeCommunicate/HBigUCharConvert.h"
#include "HeCommunicate/HSerialPort.h"

HDaXinProtocol::HDaXinProtocol(QObject *parent) :
    HAbstractProtocol(*new HDaXinProtocolPrivate, parent)
{
    init();
}

HDaXinProtocol::~HDaXinProtocol() = default;

QString HDaXinProtocol::typeName()
{
    return "HDaXinProtocol";
}

void HDaXinProtocol::init()
{
    Q_D(HDaXinProtocol);
    QVariantMap param;
    param.insert("timeOut", 1000);
    param.insert("baudRate", 38400);
    auto port = new HSerialPort(this);
    port->initialize(param);
    d->convert = new HBigUCharConvert(this);
    d->device = new HDaXinDevice(this);
    d->device->setPort(port, 4, true);
    d->device->addActionParam(ACT_SET_OUTPUT_VOLTAGE,     QList<uchar>() << 0x00 << 0x02 << 0x20);
    d->device->addActionParam(ACT_SET_OUTPUT_CURRENT,     QList<uchar>() << 0x00 << 0x02 << 0x21);
    d->device->addActionParam(ACT_SET_OVER_VOLTAGE,       QList<uchar>() << 0x00 << 0x02 << 0x22);
    d->device->addActionParam(ACT_SET_OVER_CURRENT,       QList<uchar>() << 0x00 << 0x02 << 0x23);
    d->device->addActionParam(ACT_SET_SOURCE_MODE,        QList<uchar>() << 0x00 << 0x02 << 0x24);
    d->device->addActionParam(ACT_SET_SOURCE_ADDR,        QList<uchar>() << 0x00 << 0x02 << 0x25);
    d->device->addActionParam(ACT_SET_SOURCE_OPERATION,   QList<uchar>() << 0x00 << 0x02 << 0x26);
    d->device->addActionParam(ACT_SET_SOURCE_FORWARD,     QList<uchar>() << 0x00 << 0x02 << 0x30);
    d->device->addActionParam(ACT_SET_SOURCE_REVERSE,     QList<uchar>() << 0x00 << 0x02 << 0x31);
    d->device->addActionParam(ACT_SET_SOURCE_IO,          QList<uchar>() << 0x00 << 0x02 << 0x32);
    d->device->addActionParam(ACT_GET_SOURCE_STATE,       QList<uchar>() << 0x00 << 0x01 << 0x27);
    d->device->addActionParam(ACT_GET_ELEC_DATA,          QList<uchar>() << 0x00 << 0x05 << 0x28);
}
