#include "HAbstractPort_p.h"
#include "HeCore/HCoreHelper.h"
#include "HeCore/HException.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

HAbstractPort::HAbstractPort(QObject *parent) :
    QObject(parent),
    d_ptr(new HAbstractPortPrivate)
{
}

HAbstractPort::HAbstractPort(HAbstractPortPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HAbstractPort::~HAbstractPort() = default;

void HAbstractPort::initialize(QVariantMap param)
{
    if (param.contains("timeOut"))
        setTimeOut(param.value("timeOut").toInt());
}

bool HAbstractPort::isConnected()
{
    return d_ptr->connected;
}

void HAbstractPort::setTimeOut(int value)
{
    d_ptr->timeOut = value;
}

bool HAbstractPort::open(int num)
{
    if (isConnected())
        return true;
    if (!openPort(num))
        return false;
    d_ptr->connected = true;
    return true;
}

bool HAbstractPort::close()
{
    if (!d_ptr->connected)
        return true;

    if (!closePort())
        return false;
    d_ptr->connected = false;
    return true;
}

bool HAbstractPort::clear()
{
    if (!d_ptr->connected)
        return false;
    QVector<uchar> data(100);
    read(data);
    return true;
}

int HAbstractPort::write(QVector<uchar> data)
{
    return writeData(data.data(), data.size());
}

int HAbstractPort::read(QVector<uchar> &data)
{
    return readData(data.data(), data.size());
}

bool HAbstractPort::transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay)
{
    auto size1 = downData.size();
    auto size2 = upData.size();
    if (write(downData) < size1)
        throw HException(E_PORT_WRITE_DATA_LESS);
    if (delay > 10)
        HCoreHelper::msleep(delay);
    if (read(upData) < size2)
        throw HException(E_PORT_READ_DATA_LESS);
    return true;
}

HE_END_NAMESPACE

