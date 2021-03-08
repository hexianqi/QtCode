#include "HAbstractDevice_p.h"
#include "IPort.h"
#include "HeCore/HException.h"
#include <QtCore/QVector>

HE_COMMUNICATE_BEGIN_NAMESPACE

HAbstractDevice::HAbstractDevice() :
    d_ptr(new HAbstractDevicePrivate)
{
}

HAbstractDevice::HAbstractDevice(HAbstractDevicePrivate &p) :
    d_ptr(&p)
{
}

HAbstractDevice::~HAbstractDevice() = default;

void HAbstractDevice::initialize(QVariantMap param)
{
    if (param.contains("port"))
        d_ptr->port = FromVariant(IPort, param.value("port"));
    if (param.contains("portNum"))
        d_ptr->portNum = param.value("portNum").toInt();
    if (param.contains("portNumScan"))
        d_ptr->portNumScan = param.value("portNumScan").toBool();
    if (param.contains("deviceID"))
        d_ptr->deviceID = param.value("deviceID").toInt();
    if (param.contains("action"))
        d_ptr->actionParams = param.value("action").value<QMap<HActionType, QList<uchar>>>();
    if (d_ptr->port != nullptr)
        d_ptr->port->initialize(param);
}

QString HAbstractDevice::portType()
{
    if (d_ptr->port == nullptr)
        return "unknown";
    return d_ptr->port->portType();
}

bool HAbstractDevice::isSupport(HActionType action)
{
    return d_ptr->actionParams.contains(action);
}

void HAbstractDevice::setPort(IPort* port, int num, bool scan)
{
    d_ptr->port = port;
    d_ptr->portNum = num;
    d_ptr->portNumScan = scan;
}

void HAbstractDevice::setDeviceID(int value)
{
    d_ptr->deviceID = value;
}

void HAbstractDevice::addActionParam(HActionType action, QList<uchar> value)
{
    d_ptr->actionParams.insert(action, value);
}

bool HAbstractDevice::open()
{
    if (d_ptr->port == nullptr)
        throw HException(E_PORT_INVALID);
    close();
    if (!d_ptr->portNumScan)
        return open(d_ptr->portNum);

    if (tryOpen(d_ptr->portNum))
        return true;

    for (int i = 1; i < 10; i++)
    {
        if (tryOpen(i))
        {
            d_ptr->portNum = i;
            return true;
        }
    }
    throw HException(E_DEVICE_NOT_FOUND);
}

bool HAbstractDevice::close()
{
    if (d_ptr->port != nullptr)
        return d_ptr->port->close();
    return true;
}

bool HAbstractDevice::open(int num)
{
    try
    {
        if (!d_ptr->port->open(num))
            return false;
        if (check())
            return true;
    }
    catch (HException &e)
    {
        d_ptr->port->close();
        e.raise();
    }
    return false;
}

bool HAbstractDevice::tryOpen(int num)
{
    try
    {
        if (open(num))
            return true;
    }
    catch (HException &)
    {
    }
    return false;
}

bool HAbstractDevice::check()
{
    QVector<uchar> data;
    return getData(ACT_CHECK_DEVICE, data);
}

void HAbstractDevice::transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay)
{
    d_ptr->port->transport(downData, upData, delay);
}

HE_COMMUNICATE_END_NAMESPACE

