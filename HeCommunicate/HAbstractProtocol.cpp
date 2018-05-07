#include "HAbstractProtocol_p.h"
#include "IPort.h"
#include "IProtocolInfo.h"
#include <QMutex>
#include <QVector>

HE_CORE_USE_NAMESPACE
HE_COMMUNICATE_USE_NAMESPACE

HAbstractProtocolPrivate::HAbstractProtocolPrivate()
{
    mutex = new QMutex();
}

HAbstractProtocol::HAbstractProtocol(QObject *parent)
    : QObject(parent), d_ptr(new HAbstractProtocolPrivate)
{
}

HAbstractProtocol::HAbstractProtocol(HAbstractProtocolPrivate &p, QObject *parent)
    : QObject(parent), d_ptr(&p)
{
}

HAbstractProtocol::~HAbstractProtocol()
{
    close();
}

void HAbstractProtocol::initialize(QVariantMap param)
{
    if (param.contains("protocolInfo"))
        setProtocolInfo(static_cast<IProtocolInfo *>(param.value("protocolInfo").value<void *>()));
}

void HAbstractProtocol::setProtocolInfo(IProtocolInfo *info)
{
    close();
    d_ptr->info = info;
    d_ptr->port = info->port();
}

HErrorType HAbstractProtocol::open()
{
    close();
    QMutexLocker locker(d_ptr->mutex);

    if (d_ptr->info == nullptr)
        return E_PROTOCOL_INFO_INVALID;
    if (d_ptr->port == nullptr)
        return E_PORT_INVALID;

    auto error = openPort(d_ptr->info->portNum());
    if (error == E_OK || !d_ptr->info->isPortNumScan())
        return error;

    for (int i = 0; i < 10; i++)
    {
        error = openPort(i);
        if (error == E_OK)
        {
            d_ptr->info->setPortNum(i);
            return E_OK;
        }
    }
    return E_DEVICE_NO_FOUND;
}

HErrorType HAbstractProtocol::close()
{
    if (d_ptr->port != nullptr)
        d_ptr->port->close();
    return E_OK;
}

HErrorType HAbstractProtocol::setData(HActionType action, int value, int delay)
{
    QVector<uchar> data;
    data << uchar(value % 256) << uchar(value / 256);
    return setData(action, data, delay);
}

HErrorType HAbstractProtocol::setData(HActionType action, double value, double factor, int delay)
{
    return setData(action, int(value * factor), delay);
}

HErrorType HAbstractProtocol::setData(HActionType action, uchar value, int delay)
{
    QVector<uchar> data;
    data << value;
    return setData(action, data, delay);
}

HErrorType HAbstractProtocol::setData(HActionType action, uint value, int delay)
{
    QVector<uchar> data;
    data.append((value >>  0) & 0xFF);
    data.append((value >>  8) & 0xFF);
    data.append((value >> 16) & 0xFF);
    data.append((value >> 24) & 0xFF);
    return setData(action, data, delay);
}

HErrorType HAbstractProtocol::setData(HActionType action, QVector<int> value, int delay)
{
    QVector<uchar> data;
    for (auto i : value)
        data << uchar(i % 256) << uchar(i / 256);
    return setData(action, data, delay);
}

HErrorType HAbstractProtocol::setData(HActionType action, QVector<double> value, double factor, int delay)
{
    QVector<uchar> data;
    for (auto d : value)
    {
        int i = int(d * factor);
        data << uchar(i % 256) << uchar(i / 256);
    }
    return setData(action, data, delay);
}

HErrorType HAbstractProtocol::setData(HActionType action, QVector<uchar> value, int delay)
{
    return interactionSet(action, value, delay);
}

HErrorType HAbstractProtocol::setData(HActionType action, QVector<uint> value, int delay)
{
    QVector<uchar> data;
    for (auto i : value)
    {
        data.append((i >>  0) & 0xFF);
        data.append((i >>  8) & 0xFF);
        data.append((i >> 16) & 0xFF);
        data.append((i >> 24) & 0xFF);
    }
    return setData(action, data, delay);
}

HErrorType HAbstractProtocol::getData(HActionType action, int &value, int delay)
{
    QVector<uchar> data;
    auto error = getData(action, data, delay);
    if (error != E_OK)
        return error;
    value = data[0] + data[1] * 256;
    return E_OK;
}

HErrorType HAbstractProtocol::getData(HActionType action, double &value, double factor, int delay)
{
    QVector<uchar> data;
    auto error = getData(action, data, delay);
    if (error != E_OK)
        return error;
    value = (data[0] + data[1] * 256) * factor;
    return E_OK;
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

HErrorType HAbstractProtocol::getData(HActionType action, uint &value, int delay)
{
    QVector<uchar> data;
    auto error = getData(action, data, delay);
    if (error != E_OK)
        return error;
    value = data[0] + data[1] * 256 + data[2] * 256 * 256 + data[3] * 256 * 256 * 256;
    return E_OK;
}

HErrorType HAbstractProtocol::getData(HActionType action, QVector<int> &value, int delay)
{
    QVector<uchar> data;
    auto error = getData(action, data, delay);
    if (error != E_OK)
        return error;
    if (value.size() == 0)
        value.resize(data.size() / 2);
    auto size = qMin(value.size(), data.size() / 2);
    for (int i = 0; i < size; i++)
        value[i] = data[2 * i] + data[2 * i + 1] * 256;
    return E_OK;
}

HErrorType HAbstractProtocol::getData(HActionType action, QVector<double> &value, double factor, int delay)
{
    QVector<uchar> data;
    auto error = getData(action, data, delay);
    if (error != E_OK)
        return error;
    if (value.size() == 0)
        value.resize(data.size()/2);
    auto size = qMin(value.size(), data.size() / 2);
    for (int i = 0; i < size; i++)
        value[i] = (data[2 * i] + data[2 * i + 1] * 256) * factor;
    return E_OK;
}

HErrorType HAbstractProtocol::getData(HActionType action, QVector<uchar> &value, int delay)
{
    return interactionGet(action, value, delay);
}

HErrorType HAbstractProtocol::getData(HActionType action, QVector<uint> &value, int delay)
{
    QVector<uchar> data;
    auto error = getData(action, data, delay);
    if (error != E_OK)
        return error;
    if (value.size() == 0)
        value.resize(data.size() / 4);
    auto size = qMin(value.size(), data.size() / 4);
    for (int i = 0; i < size; i++)
        value[i] = data[4 * i] + data[4 * i + 1] * 256 + data[4 * i + 2] * 256 * 256 + data[4 * i + 3] * 256 * 256 * 256;
    return E_OK;
}

HErrorType HAbstractProtocol::openPort(int num)
{
    auto error = d_ptr->port->open(num);
    if (error != E_OK)
        return error;

    error = checkDevice();
    if (error != E_OK)
        d_ptr->port->close();
    return error;
}

