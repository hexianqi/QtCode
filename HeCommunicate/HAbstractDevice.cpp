#include "HAbstractDevice_p.h"
#include "IPort.h"
#include <QVector>

HE_COMMUNICATE_USE_NAMESPACE

HAbstractDevice::HAbstractDevice(QObject *parent)
    : QObject(parent), d_ptr(new HAbstractDevicePrivate)
{
}

HAbstractDevice::HAbstractDevice(HAbstractDevicePrivate &p, QObject *parent)
    : QObject(parent), d_ptr(&p)
{
}

HAbstractDevice::~HAbstractDevice()
{
    close();
}

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
}

bool HAbstractDevice::isSupport(HActionType action)
{
    return d_ptr->actionParam.contains(action);
}

void HAbstractDevice::setPort(IPort *port, int num, bool scan)
{
    d_ptr->port = port;
    d_ptr->portNum = num;
    d_ptr->portNumScan = scan;
}

void HAbstractDevice::setDeviceID(int id)
{
    d_ptr->deviceID = id;
}

void HAbstractDevice::addActionParam(HActionType key, QList<uchar> value)
{
    d_ptr->actionParam.insert(key, value);
}

HErrorType HAbstractDevice::open()
{
    if (d_ptr->port == nullptr)
        return E_PORT_INVALID;

    close();
    auto error = open(d_ptr->portNum);
    if (error == E_OK || !d_ptr->portNumScan)
        return error;

    for (int i = 0; i < 10; i++)
    {
        error = open(i);
        if (error == E_OK)
        {
            d_ptr->portNum = i;
            return E_OK;
        }
    }
    return E_DEVICE_NO_FOUND;
}

HErrorType HAbstractDevice::close()
{
    if (d_ptr->port != nullptr)
        d_ptr->port->close();
    return E_OK;
}

HErrorType HAbstractDevice::open(int num)
{
    auto error = d_ptr->port->open(num);
    if (error != E_OK)
        return error;

    error = check();
    if (error != E_OK)
        d_ptr->port->close();
    return error;
}

HErrorType HAbstractDevice::check()
{
    QVector<uchar> data;
    return getData(ACT_CHECK_DEVICE, data);
}
