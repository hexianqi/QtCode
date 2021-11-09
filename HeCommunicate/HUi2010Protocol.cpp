#include "HUi2010Protocol_p.h"
#include "HSerialPort.h"
#include "HPowerFactorDevice.h"
#include <QtCore/QDebug>

HE_COMMUNICATE_BEGIN_NAMESPACE

union CharFloat
{
    float f;
    unsigned char c[4];
};

HUi2010ProtocolPrivate::HUi2010ProtocolPrivate()
{
    QVariantMap param;
    param.insert("timeOut", 1000);
    param.insert("baudRate", 19200);
    auto port = new HSerialPort();
    port->initialize(param);
    device = new HPowerFactorDevice;
    device->setPort(port, 4, true);
    device->addActionParam(ACT_CHECK_DEVICE,    QList<uchar>() << 0x00 << 0x14 << 0x33);
    device->addActionParam(ACT_GET_ELEC_DATA,   QList<uchar>() << 0x00 << 0x14 << 0x33);
}

HUi2010Protocol::HUi2010Protocol() :
    HLittleProtocol(*new HUi2010ProtocolPrivate)
{
}

HUi2010Protocol::~HUi2010Protocol()
{
    qDebug() << __func__;
}

QString HUi2010Protocol::typeName()
{
    return "HUi2010Protocol";
}

bool HUi2010Protocol::getData(HActionType action, QVector<double> &value, int delay)
{
    QVector<uchar> data;
    HLittleProtocol::getData(action, data, delay);
    if (value.isEmpty())
        value.resize(data.size() / 4);
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

HE_COMMUNICATE_END_NAMESPACE
