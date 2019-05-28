#include "HAbstractProtocol_p.h"
#include "IDevice.h"
#include <QtCore/QMutex>
#include <QtCore/QVector>

HE_COMMUNICATE_BEGIN_NAMESPACE

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

HAbstractProtocol::~HAbstractProtocol()
{
    close();
}

void HAbstractProtocol::initialize(QVariantMap param)
{
    if (param.contains("device"))
        setDevice(FromVariant(IDevice, param.value("device")));
}

void HAbstractProtocol::setDevice(IDevice *p)
{
    close();
    d_ptr->device = p;
}

HErrorType HAbstractProtocol::open()
{
    QMutexLocker locker(d_ptr->mutex);
    if (d_ptr->device == nullptr)
        return E_DEVICE_INVALID;
    return d_ptr->device->open();
}

HErrorType HAbstractProtocol::close()
{
    if (d_ptr->device != nullptr)
        d_ptr->device->close();
    return E_OK;
}

HErrorType HAbstractProtocol::setData(HActionType action, uchar value, int delay)
{
    QVector<uchar> data;
    data << value;
    return setData(action, data, delay);
}

HErrorType HAbstractProtocol::setData(HActionType action, QVector<uchar> value, int delay)
{
    return d_ptr->device->setData(action, value, delay);
}

HErrorType HAbstractProtocol::getData(HActionType action, uchar &value, int delay)
{
    QVector<uchar> data;
    auto error = getData(action, data, delay);
    if (error != E_OK)
        return error;
    value = data[0];
    return E_OK;
}

HErrorType HAbstractProtocol::getData(HActionType action, QVector<uchar> &value, int delay)
{
    return d_ptr->device->getData(action, value, delay);
}

HE_COMMUNICATE_END_NAMESPACE
