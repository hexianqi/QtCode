#include "HAbstractPort_p.h"
#include "HeCore/HCore.h"
#include <QVector>

HE_COMMUNICATE_USE_NAMESPACE

HAbstractPort::HAbstractPort(QObject *parent)
    : QObject(parent), d_ptr(new HAbstractPortPrivate)
{
}

HAbstractPort::HAbstractPort(HAbstractPortPrivate &p, QObject *parent)
    : QObject(parent), d_ptr(&p)
{
}

HAbstractPort::~HAbstractPort()
{
    close();
}

void HAbstractPort::initialize(QVariantMap param)
{
    if (param.contains("timeOut"))
        d_ptr->timeOut = param.value("timeOut").toInt();
}

bool HAbstractPort::isConnected()
{
    return d_ptr->isConnect;
}

HErrorType HAbstractPort::open(int portNum)
{
    if (isConnected())
        return E_PORT_OPENED;
    auto error = openPort(portNum);
    if (error != E_OK)
        return error;
    d_ptr->portNum = portNum;
    d_ptr->isConnect = true;
    clear();
    return E_OK;
}

HErrorType HAbstractPort::close()
{
    if (!isConnected())
        return E_PORT_CLOSED;

    auto error = closePort();
    if (error != E_OK)
        return error;
    d_ptr->isConnect = false;
    return E_OK;
}

HErrorType HAbstractPort::transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay)
{
    auto error = write(downData);
    if (error != E_OK)
        return error;

    if (delay >= 10)
        HeCore::msleep(delay);

    return read(upData);
}

HErrorType HAbstractPort::clear()
{
    if (!isConnected())
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
