#include "HSimulateDevice_p.h"
#include "HeCore/HException.h"
#include <QtCore/QtMath>
#include <QtCore/QRandomGenerator>
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

HSimulateDevicePrivate::HSimulateDevicePrivate()
{
    actionParams.insert(ACT_GET_ELEC_DATA,               QList<uchar>() << 0x00 << 0x06);
    actionParams.insert(ACT_GET_ANGLE_DISTRIBUTION,      QList<uchar>() << 0x01 << 0x92);
}

HSimulateDevice::HSimulateDevice(QObject *parent) :
    HAbstractDevice(*new HSimulateDevicePrivate, parent)
{
}

HSimulateDevice::HSimulateDevice(HSimulateDevicePrivate &p, QObject *parent) :
    HAbstractDevice(p, parent)
{
}

HSimulateDevice::~HSimulateDevice() = default;

QString HSimulateDevice::typeName()
{
    return "HSimulateDevice";
}

bool HSimulateDevice::open()
{
    return true;
}

bool HSimulateDevice::close()
{
    return true;
}

bool HSimulateDevice::setData(HActionType /*action*/, QVector<uchar> /*value*/, int /*delay*/)
{
    return true;
}

bool HSimulateDevice::getData(HActionType action, QVector<uchar> &value, int /*delay*/)
{
    Q_D(HSimulateDevice);
    auto param = d->actionParams.value(action);
    if (param.size() < 2)
        param = QList<uchar>() << 0x00 << 0x02;

    value.clear();
    if (action == ACT_QUERY_STATE_TRIGGER || action == ACT_QUERY_MOTOR_STATE)
    {
        value << 0x01 << 0x00;
    }
    else if (action == ACT_GET_ANGLE_DISTRIBUTION)
    {
        for (int i = 0; i < 201; i++)
        {
            auto r = qDegreesToRadians(180.0 * i / 201);
            auto t = 60000 * sin(r);
            auto p = 0.95 + QRandomGenerator::global()->generateDouble() * 0.1;
            auto v = int(t * p);
            value << uchar(v % 256);
            value << uchar(v / 256);
        }
    }
    else
    {
        auto size =  param[0] * 256 + param[1];
        for (int i = 0; i < size; i++)
            value << simulate(255);
    }
    return true;
}

uchar HSimulateDevice::simulate(int value)
{
    return QRandomGenerator::global()->bounded(value);
}

HE_END_NAMESPACE
