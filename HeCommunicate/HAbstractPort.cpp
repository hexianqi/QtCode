#include "HAbstractPort_p.h"
#include "HeCore/HCoreHelper.h"
#include <QtCore/QVector>

HE_COMMUNICATE_BEGIN_NAMESPACE

HAbstractPort::HAbstractPort() :
    d_ptr(new HAbstractPortPrivate)
{
}

HAbstractPort::HAbstractPort(HAbstractPortPrivate &p) :
    d_ptr(&p)
{
}

void HAbstractPort::initialize(QVariantMap param)
{
    if (param.contains("timeOut"))
        setTimeOut(param.value("timeOut").toInt());
}

void HAbstractPort::setTimeOut(int value)
{
    d_ptr->timeOut = value;
}

bool HAbstractPort::isConnected()
{
    return d_ptr->connected;
}

HErrorType HAbstractPort::open(int portNum)
{
    if (isConnected())
        return E_PORT_OPENED;
    auto error = openPort(portNum);
    if (error != E_OK)
        return error;
    d_ptr->portNum = portNum;
    d_ptr->connected = true;
    clear();
    return E_OK;
}

HErrorType HAbstractPort::close()
{
    if (!d_ptr->connected)
        return E_PORT_CLOSED;

    auto error = closePort();
    if (error != E_OK)
        return error;
    d_ptr->connected = false;
    return E_OK;
}

HErrorType HAbstractPort::clear()
{
    if (!d_ptr->connected)
        return E_PORT_CLOSED;
    QVector<uchar> data(100);
    read(data);
    return E_OK;
}

HErrorType HAbstractPort::write(QVector<uchar> data)
{
    return writeData(data.data(), data.size());
}

HErrorType HAbstractPort::read(QVector<uchar> &data)
{
    return readData(data.data(), data.size());
}

HErrorType HAbstractPort::transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay)
{
    auto error = write(downData);
    if (error != E_OK)
        return error;

    if (delay > 10)
        HCoreHelper::msleep(delay);
    return read(upData);
}

HE_COMMUNICATE_END_NAMESPACE

