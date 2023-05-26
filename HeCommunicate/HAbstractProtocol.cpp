#include "HAbstractProtocol_p.h"
#include "IDevice.h"
#include "IUCharConvert.h"
#include "HeCore/HDefine.h"
#include "HeCore/HException.h"
#include <QtCore/QMutex>
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

HAbstractProtocolPrivate::HAbstractProtocolPrivate() :
    mutex(new QMutex)
{
}

HAbstractProtocolPrivate::~HAbstractProtocolPrivate()
{
    delete mutex;
}

HAbstractProtocol::HAbstractProtocol(QObject *parent) :
    QObject(parent),
    d_ptr(new HAbstractProtocolPrivate)
{
}

HAbstractProtocol::HAbstractProtocol(HAbstractProtocolPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HAbstractProtocol::~HAbstractProtocol() = default;

void HAbstractProtocol::initialize(QVariantMap param)
{
    if (param.contains("device"))
        setDevice(FromVariant(IDevice, param.value("device")));
    if (param.contains("convert"))
        setConvert(FromVariant(IUCharConvert, param.value("convert")));
    if (d_ptr->device != nullptr)
        d_ptr->device->initialize(param);
    if (d_ptr->convert != nullptr)
        d_ptr->convert->initialize(param);
}

QString HAbstractProtocol::portType()
{
    if (d_ptr->device != nullptr)
        return d_ptr->device->portType();
    return "unknown";
}

void HAbstractProtocol::setDevice(IDevice *p)
{
    close();
    d_ptr->device = p;
}

void HAbstractProtocol::setConvert(IUCharConvert *p)
{
    d_ptr->convert = p;
}

void HAbstractProtocol::setPort(IPort *p, int num, bool autoScan)
{
    close();
    if (d_ptr->device != nullptr)
        d_ptr->device->setPort(p, num, autoScan);
}

bool HAbstractProtocol::open()
{
    QMutexLocker locker(d_ptr->mutex);
    if (d_ptr->device != nullptr)
        return d_ptr->device->open();
    throw HException(E_DEVICE_INVALID);
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
bool HAbstractProtocol::setData(HActionType action, QVariant value, int delay)
{
    if (d_ptr->convert == nullptr)
        throw HException(E_CONVERT_INVALID_UCHAR);
    return setData(action, d_ptr->convert->toUChar(value), delay);
}

bool HAbstractProtocol::setData(HActionType action, QVariantList value, int delay)
{
    if (d_ptr->convert == nullptr)
        throw HException(E_CONVERT_INVALID_UCHAR);
    return setData(action, d_ptr->convert->toUChar(value), delay);
}

bool HAbstractProtocol::setData(HActionType action, QVector<uchar> value, int delay)
{
    if (d_ptr->device != nullptr)
        return d_ptr->device->setData(action, value, delay);
    throw HException(E_DEVICE_INVALID);
}

bool HAbstractProtocol::getData(HActionType action)
{
    QVector<uchar> data;
    return getData(action, data);
}

bool HAbstractProtocol::getData(HActionType action, QVariant &value, QVariant::Type type, int delay)
{
    if (d_ptr->convert == nullptr)
        throw HException(E_CONVERT_INVALID_UCHAR);
    QVector<uchar> data;
    if (!getData(action, data, delay))
        return false;
    value = d_ptr->convert->toValue(type, data);
    return true;
}

bool HAbstractProtocol::getData(HActionType action, QVariantList &value, QVariant::Type type, int delay)
{
    if (d_ptr->convert == nullptr)
        throw HException(E_CONVERT_INVALID_UCHAR);
    QVector<uchar> data;
    if (!getData(action, data, delay))
        return false;
    value = d_ptr->convert->toValues(type, data, value.size());
    return true;
}

bool HAbstractProtocol::getData(HActionType action, QVector<uchar> &value, int delay)
{
    if (d_ptr->device != nullptr)
        return d_ptr->device->getData(action, value, delay);
    throw HException(E_DEVICE_INVALID);
}

HE_END_NAMESPACE
