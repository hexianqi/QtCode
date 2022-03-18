#include "HKeyenceProtocol_p.h"
#include "HKeyenceDevice.h"
#include "HeCommunicate/HSerialPort.h"

HKeyenceProtocolPrivate::HKeyenceProtocolPrivate()
{
    QVariantMap param;
    param.insert("timeOut", 1000);
    param.insert("baudRate", 57600);
    param.insert("parity", 2);
    auto port = new HSerialPort();
    port->initialize(param);
    device = new HKeyenceDevice;
    device->setPort(port, 3, false);
    device->addActionParam(ACT_SET_MOTOR_LOCATION,      QList<uchar>() << 0x00 << 0x00);
    device->addActionParam(ACT_RESET_MOTOR_LOCATION,    QList<uchar>() << 0x63 << 0x63);
    device->addActionParam(ACT_SET_MOTOR_PREPARE_TEST,  QList<uchar>() << 0x58 << 0x58);
    device->addActionParam(ACT_SET_MOTOR_CANCEL_TEST,   QList<uchar>() << 0x4D << 0x4D);
    device->addActionParam(ACT_QUERY_MOTOR_STATE,       QList<uchar>() << 0x00 << 0x00);
}

HKeyenceProtocol::HKeyenceProtocol() :
    HBigProtocol(*new HKeyenceProtocolPrivate)
{
}

HKeyenceProtocol::HKeyenceProtocol(HKeyenceProtocolPrivate &p) :
    HBigProtocol(p)
{
}

HKeyenceProtocol::~HKeyenceProtocol() = default;

void HKeyenceProtocol::initialize(QVariantMap param)
{
    Q_D(HKeyenceProtocol);
    d->device->initialize(param);
}

QString HKeyenceProtocol::typeName()
{
    return "HKeyenceProtocol";
}
