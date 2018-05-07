#include "HAbstractProtocolStrategy_p.h"
#include "IPort.h"
#include <QVector>

HE_COMMUNICATE_USE_NAMESPACE

HAbstractProtocolStrategy::HAbstractProtocolStrategy()
    : d_ptr(new HAbstractProtocolStrategyPrivate)
{
}

HAbstractProtocolStrategy::HAbstractProtocolStrategy(HAbstractProtocolStrategyPrivate &p)
    : d_ptr(&p)
{
}

HAbstractProtocolStrategy::~HAbstractProtocolStrategy()
{
    close();
}

void HAbstractProtocolStrategy::initialize(QVariantMap param)
{
    if (param.contains("port"))
        d_ptr->port = static_cast<IPort *>(param.value("port").value<void *>());
    if (param.contains("portNum"))
        d_ptr->portNum = param.value("portNum").toInt();
    if (param.contains("portNumScan"))
        d_ptr->portNumScan = param.value("portNumScan").toBool();
    if (param.contains("deviceID"))
        d_ptr->deviceID = param.value("deviceID").toInt();
}

void HAbstractProtocolStrategy::setPort(IPort *port, int num, bool scan)
{
    d_ptr->port = port;
    d_ptr->portNum = num;
    d_ptr->portNumScan = scan;
}

void HAbstractProtocolStrategy::setDeviceID(int id)
{
    d_ptr->deviceID = id;
}

void HAbstractProtocolStrategy::addActionParam(HActionType key, QList<uchar> value)
{
    d_ptr->actionParam.insert(key, value);
}

HErrorType HAbstractProtocolStrategy::open()
{
    if (d_ptr->port == nullptr)
        return E_PORT_INVALID;

    close();
    auto error = openDevice(d_ptr->portNum);
    if (error == E_OK || !d_ptr->portNumScan)
        return error;

    for (int i = 0; i < 10; i++)
    {
        error = openDevice(i);
        if (error == E_OK)
        {
            d_ptr->portNum = i;
            return E_OK;
        }
    }
    return E_DEVICE_NO_FOUND;
}

HErrorType HAbstractProtocolStrategy::close()
{
    if (d_ptr->port != nullptr)
        d_ptr->port->close();
    return E_OK;
}

HErrorType HAbstractProtocolStrategy::openDevice(int num)
{
    auto error = d_ptr->port->open(num);
    if (error != E_OK)
        return error;

    error = checkDevice();
    if (error != E_OK)
        d_ptr->port->close();
    return error;
}

HErrorType HAbstractProtocolStrategy::checkDevice()
{
    QVector<uchar> data;
    return getData(ACT_CHECK_DEVICE, data);
}
