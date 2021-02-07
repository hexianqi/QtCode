#include "HSimulateDevice_p.h"
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>

HE_COMMUNICATE_BEGIN_NAMESPACE

HSimulateDevice::HSimulateDevice() :
    HAbstractDevice(*new HSimulateDevicePrivate)
{
}

HSimulateDevice::HSimulateDevice(HSimulateDevicePrivate &p) :
    HAbstractDevice(p)
{
}

HSimulateDevice::~HSimulateDevice()
{
    qDebug() << __func__;
}

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
    value.clear();
    if (action == ACT_QUERY_STATE_TRIGGER)
    {
        value << 0x01 << 0x00;
    }
    else if (action == ACT_GET_ELEC_DATA)
    {
        for (int i = 0; i < 6; i++)
            value << simulate(255);
    }
    else
    {
        value << simulate(255) << simulate(255);
    }
    return true;
}

uchar HSimulateDevice::simulate(int value)
{
    return QRandomGenerator::global()->bounded(value);
}

HE_COMMUNICATE_END_NAMESPACE
