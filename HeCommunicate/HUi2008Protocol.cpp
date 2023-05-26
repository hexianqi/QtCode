#include "HUi2008Protocol_p.h"
#include "HSerialPort.h"
#include "HPowerFactorDevice.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

HUi2008Protocol::HUi2008Protocol(QObject *parent) :
    HAbstractProtocol(*new HUi2008ProtocolPrivate, parent)
{
    init();
}

HUi2008Protocol::~HUi2008Protocol() = default;

QString HUi2008Protocol::typeName()
{
    return "HUi2008Protocol";
}

bool HUi2008Protocol::getData(HActionType action, QVariantList &value, QVariant::Type /*type*/, int delay)
{
    QVector<uchar> data;
    if (!HAbstractProtocol::getData(action, data, delay))
        return false;

    if (value.isEmpty())
        value.reserve(data.size() / 4);

    int i,j,n,v;
    double t;
    auto size = qMin(value.size(), data.size() / 4);
    for (i = 0; i < size; i++)
    {
        n = 0;
        t = 0.0;
        for (j = 0; j < 4; j++)
        {
            v = data[1 + 4 * i + j];
            if (v >= 0x1B)
                v = 0x00;
            if (v >= 0x10)
            {
                v -= 0x10;
                n = j;
            }
            t = t * 10 + v;
        }
        value[i] = t * pow(0.1, 3 - n);
    }
    return true;
}

void HUi2008Protocol::init()
{
    Q_D(HUi2008Protocol);
    QVariantMap param;
    param.insert("timeOut", 1000);
    param.insert("baudRate", 4800);
    auto port = new HSerialPort(this);
    port->initialize(param);
    d->device = new HPowerFactorDevice(this);
    d->device->setPort(port, 4, true);
    d->device->addActionParam(ACT_CHECK_DEVICE,    QList<uchar>() << 0x00 << 0x15 << 0x3F);
    d->device->addActionParam(ACT_GET_ELEC_DATA,   QList<uchar>() << 0x00 << 0x15 << 0x3F);
}

HE_END_NAMESPACE
