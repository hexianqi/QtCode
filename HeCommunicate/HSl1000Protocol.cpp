#include "HSl1000Protocol_p.h"
#include "HLittleUCharConvert.h"
#include "HSerialPort.h"
#include "HSlDevice3.h"

HE_BEGIN_NAMESPACE

HSl1000Protocol::HSl1000Protocol(QObject *parent) :
    HAbstractProtocol(*new HSl1000ProtocolPrivate, parent)
{
    init();
}

HSl1000Protocol::HSl1000Protocol(HSl1000ProtocolPrivate &p, QObject *parent) :
    HAbstractProtocol(p, parent)
{
}

HSl1000Protocol::~HSl1000Protocol() = default;

QString HSl1000Protocol::typeName()
{
    return "HSl1000Protocol";
}

void HSl1000Protocol::init()
{
    Q_D(HSl1000Protocol);
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
    d->device->addActionParam(ACT_GET_ELEC_DATA,               QList<uchar>() << 0x00 << 0x06 << 0x01 << 0x11);
    d->device->addActionParam(ACT_GET_MEASURED_VOLTAGE,        QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x12);
    d->device->addActionParam(ACT_GET_MEASURED_CURRENT,        QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x13);
    d->device->addActionParam(ACT_GET_REVERSE_CURRENT,         QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x14);
    d->device->addActionParam(ACT_RESET_STATE_TRIGGER,         QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x0F);
    d->device->addActionParam(ACT_QUERY_STATE_TRIGGER,         QList<uchar>() << 0x00 << 0x02 << 0x01 << 0x15);
    d->device->addActionParam(ACT_SET_LUMINOUS_TYPE,           QList<uchar>() << 0x00 << 0x02 << 0x02 << 0x05);
    d->device->addActionParam(ACT_SET_LUMINOUS_GEARS,          QList<uchar>() << 0x00 << 0x02 << 0x02 << 0x06);
    d->device->addActionParam(ACT_GET_LUMINOUS_DATA,           QList<uchar>() << 0x00 << 0x02 << 0x02 << 0x11);
    d->device->addActionParam(ACT_START_ANGLE_TEST,            QList<uchar>() << 0x00 << 0x02 << 0x02 << 0x14);
    d->device->addActionParam(ACT_GET_ANGLE_DISTRIBUTION,      QList<uchar>() << 0x01 << 0x92 << 0x02 << 0x12);
    d->device->addActionParam(ACT_RESET_MOTOR_LOCATION,        QList<uchar>() << 0x00 << 0x02 << 0x02 << 0x13);
    d->device->addActionParam(ACT_SET_MOTOR_LOCATION,          QList<uchar>() << 0x00 << 0x02 << 0x02 << 0x16);
    d->device->addActionParam(ACT_QUERY_MOTOR_STATE,           QList<uchar>() << 0x00 << 0x02 << 0x02 << 0x15);
}

HE_END_NAMESPACE
