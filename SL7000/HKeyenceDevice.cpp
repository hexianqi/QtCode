#include "HKeyenceDevice_p.h"
#include "HeCore/HException.h"
#include "HeCommunicate/IPort.h"
#include <QtCore/QVector>

HKeyenceDevice::HKeyenceDevice() :
    HAbstractDevice(*new HKeyenceDevicePrivate)
{
}

HKeyenceDevice::~HKeyenceDevice() = default;

QString HKeyenceDevice::typeName()
{
    return "HKeyenceDevice";
}

bool HKeyenceDevice::setData(HActionType action, QVector<uchar> value, int /*delay*/)
{
    Q_D(HKeyenceDevice);
    auto param = d->actionParams.value(action);
    if (param.size() < 2)
        throw HException(E_DEVICE_ACTION_PARAM_ERROR);
    if (value.isEmpty())
        value << param[0] << param[1];
    auto data = QVector<uchar>() << 0x03 << 0x00 << value << 0x66 << 0x00;
    return d_ptr->port->write(data);
}

bool HKeyenceDevice::getData(HActionType action, QVector<uchar> &value, int /*delay*/)
{
    Q_D(HKeyenceDevice);
    auto param = d->actionParams.value(action);
    if (param.size() < 3)
        throw HException(E_DEVICE_ACTION_PARAM_ERROR);

    value = QVector<uchar>() << 0x00 << 0x00;
    try
    {
        auto data = QVector<uchar>(5);
        if (d->port->read(data) == 5
            && data[0] == 0x30
            && data[1] == 0x30
            && data[2] == 0x30
            && data[3] == 0x35
            && data[4] == 0x66)
        {
            value[1] = 0x01;
        }
    }
    catch (HException &e)
    {
    }
    return true;
}

bool HKeyenceDevice::check()
{
    return true;
}
