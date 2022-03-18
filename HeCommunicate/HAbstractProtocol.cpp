#include "HAbstractProtocol_p.h"
#include "IDevice.h"
#include "HeCore/HDefine.h"
#include "HeCore/HException.h"
#include <QtCore/QMutex>
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

HAbstractProtocolPrivate::HAbstractProtocolPrivate() :
    mutex(new QMutex)
{
}

HAbstractProtocol::HAbstractProtocol() :
    d_ptr(new HAbstractProtocolPrivate)
{
}

HAbstractProtocol::HAbstractProtocol(HAbstractProtocolPrivate &p) :
    d_ptr(&p)
{
}

HAbstractProtocol::~HAbstractProtocol() = default;

void HAbstractProtocol::initialize(QVariantMap param)
{
    if (param.contains("device"))
        setDevice(FromVariant(IDevice, param.value("device")));
}

QString HAbstractProtocol::portType()
{
    if (d_ptr->device == nullptr)
        return "unknown";
    return d_ptr->device->portType();
}

void HAbstractProtocol::setDevice(IDevice *p)
{
    close();
    d_ptr->device = p;
}

bool HAbstractProtocol::open()
{
    QMutexLocker locker(d_ptr->mutex);
    if (d_ptr->device == nullptr)
        throw HException(E_DEVICE_INVALID);
    return d_ptr->device->open();
}

bool HAbstractProtocol::close()
{
    if (d_ptr->device != nullptr)
        return d_ptr->device->close();
    return true;
}

bool HAbstractProtocol::setData(HActionType action)
{
    return setData(action, QVector<uchar>());
}

bool HAbstractProtocol::setData(HActionType action, int value, int delay)
{
    auto data = toVector(value);
    return setData(action, data, delay);
}

bool HAbstractProtocol::setData(HActionType action, uchar value, int delay)
{
    auto data = QVector<uchar>() << value;
    return setData(action, data, delay);
}

bool HAbstractProtocol::setData(HActionType action, uint value, int delay)
{
    auto data = toVector(value);
    return setData(action, data, delay);
}

bool HAbstractProtocol::setData(HActionType action, double value, int delay)
{
    auto data = toVector(value);
    return setData(action, data, delay);
}

bool HAbstractProtocol::setData(HActionType action, QVector<int> value, int delay)
{
    QVector<uchar> data;
    for (auto i : value)
        data << toVector(i);
    return setData(action, data, delay);
}

bool HAbstractProtocol::setData(HActionType action, QVector<uchar> value, int delay)
{
    return d_ptr->device->setData(action, value, delay);
}

bool HAbstractProtocol::setData(HActionType action, QVector<uint> value, int delay)
{
    QVector<uchar> data;
    for (auto i : value)
        data << toVector(i);
    return setData(action, data, delay);
}

bool HAbstractProtocol::setData(HActionType action, QVector<double> value, int delay)
{
    QVector<uchar> data;
    for (auto i : value)
        data << toVector(i);
    return setData(action, data, delay);
}

bool HAbstractProtocol::getData(HActionType action)
{
    QVector<uchar> data;
    return getData(action, data);
}

bool HAbstractProtocol::getData(HActionType action, int &value, int delay)
{
    QVector<uchar> data;
    getData(action, data, delay);
    value = toInt(data);
    return true;
}

bool HAbstractProtocol::getData(HActionType action, uchar &value, int delay)
{
    QVector<uchar> data;
    getData(action, data, delay);
    value = data.first();
    return true;
}

bool HAbstractProtocol::getData(HActionType action, uint &value, int delay)
{
    QVector<uchar> data;
    getData(action, data, delay);
    value = toUInt(data);
    return true;
}

bool HAbstractProtocol::getData(HActionType action, QVector<int> &value, int delay)
{
    QVector<uchar> data;
    getData(action, data, delay);
    value = toInt(data, value.size());
    return true;
}

bool HAbstractProtocol::getData(HActionType action, QVector<uchar> &value, int delay)
{
    return d_ptr->device->getData(action, value, delay);
}

bool HAbstractProtocol::getData(HActionType action, QVector<uint> &value, int delay)
{
    QVector<uchar> data;
    getData(action, data, delay);
    value = toUInt(data, value.size());
    return true;
}

bool HAbstractProtocol::getData(HActionType action, QVector<double> &value, int delay)
{
    QVector<uchar> data;
    getData(action, data, delay);
    value = toDouble(data, value.size());
    return true;
}

HE_END_NAMESPACE
