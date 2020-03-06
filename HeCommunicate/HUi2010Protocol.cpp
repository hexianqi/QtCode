#include "HUi2010Protocol_p.h"
#include "HSerialPort.h"
#include "HPowerFactorDevice.h"
#include <QtCore/QtMath>
#include <QtCore/QDebug>

HE_COMMUNICATE_BEGIN_NAMESPACE

typedef union CharFloat
{
    float f;
    unsigned char c[4];
} CharFloat;

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
    device->addActionParam(ACT_GET_ELEC_PARAM,  QList<uchar>() << 0x00 << 0x14 << 0x33);
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

HErrorType HUi2010Protocol::getData(HActionType action, QVector<double> &value, int delay)
{
    QVector<uchar> data;
    auto error = HLittleProtocol::getData(action, data, delay);
    if (error != E_OK)
        return error;
    if (value.size() == 0)
        value.resize(data.size() / 4);
    auto size = qMin(value.size(), data.size() / 4);
    for (int i = 0; i < size; i++)
    {
        CharFloat cf;
        for (int j = 0; j < 4; j++)
            cf.c[j] = data[4 * i + j];
        value[i] = double(cf.f);
    }
    return E_OK;
}

HE_COMMUNICATE_END_NAMESPACE
