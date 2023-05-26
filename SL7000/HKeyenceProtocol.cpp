#include "HKeyenceProtocol_p.h"
#include "HKeyenceDevice.h"
#include "HeCommunicate/HBigUCharConvert.h"
#include "HeCommunicate/HSerialPort.h"

void HKeyenceProtocol::init()
{
    Q_D(HKeyenceProtocol);
    QVariantMap param;
    param.insert("timeOut", 1000);
    param.insert("baudRate", 57600);
    param.insert("parity", 2);
    auto port = new HSerialPort();
    port->initialize(param);
    d->convert = new HBigUCharConvert(this);
    d->device = new HKeyenceDevice;
    d->device->setPort(port, 3, false);
    d->device->addActionParam(ACT_SET_MOTOR_LOCATION,      QList<uchar>() << 0x00 << 0x00);
    d->device->addActionParam(ACT_RESET_MOTOR_LOCATION,    QList<uchar>() << 0x63 << 0x63);
    d->device->addActionParam(ACT_SET_MOTOR_PREPARE_TEST,  QList<uchar>() << 0x58 << 0x58);
    d->device->addActionParam(ACT_SET_MOTOR_CANCEL_TEST,   QList<uchar>() << 0x4D << 0x4D);
    d->device->addActionParam(ACT_QUERY_MOTOR_STATE,       QList<uchar>() << 0x00 << 0x00);
}

HKeyenceProtocol::HKeyenceProtocol(QObject *parent) :
    HAbstractProtocol(*new HKeyenceProtocolPrivate, parent)
{
    init();
}

HKeyenceProtocol::~HKeyenceProtocol() = default;

QString HKeyenceProtocol::typeName()
{
    return "HKeyenceProtocol";
}
