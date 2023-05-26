#include "HUi2010Protocol_p.h"
#include "HSerialPort.h"
#include "HPowerFactorDevice.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

union CharFloat
{
    float f;
    unsigned char c[4];
};

HUi2010Protocol::HUi2010Protocol(QObject *parent) :
    HAbstractProtocol(*new HUi2010ProtocolPrivate, parent)
{
    init();
}

HUi2010Protocol::~HUi2010Protocol()
{
}

QString HUi2010Protocol::typeName()
{
    return "HUi2010Protocol";
}

bool HUi2010Protocol::getData(HActionType action, QVariantList &value, QVariant::Type /*type*/, int delay)
{
    QVector<uchar> data;
    if (!HAbstractProtocol::getData(action, data, delay))
        return false;

    if (value.isEmpty())
        value.reserve(data.size() / 4);
    auto size = qMin(value.size(), data.size() / 4);
    for (int i = 0; i < size; i++)
    {
        CharFloat cf;
        for (int j = 0; j < 4; j++)
            cf.c[j] = data.at(4 * i + j);
        value[i] = double(cf.f);
    }
    return true;
}

void HUi2010Protocol::init()
{
    Q_D(HUi2010Protocol);
    QVariantMap param;
    param.insert("timeOut", 1000);
    param.insert("baudRate", 19200);
    auto port = new HSerialPort(this);
    port->initialize(param);
    d->device = new HPowerFactorDevice(this);
    d->device->setPort(port, 4, true);
    d->device->addActionParam(ACT_CHECK_DEVICE,    QList<uchar>() << 0x00 << 0x14 << 0x33);
    d->device->addActionParam(ACT_GET_ELEC_DATA,   QList<uchar>() << 0x00 << 0x14 << 0x33);
}

HE_END_NAMESPACE
