#include "HProtocol_p.h"
#include "IProtocolStrategy.h"
#include <QMutex>
#include <QVector>

HE_CORE_USE_NAMESPACE
HE_COMMUNICATE_USE_NAMESPACE

HProtocolPrivate::HProtocolPrivate()
{
    mutex = new QMutex();
}

HProtocol::HProtocol(QString name, QObject *parent)
    : QObject(parent), d_ptr(new HProtocolPrivate)
{
    setObjectName(name);
}

HProtocol::HProtocol(HProtocolPrivate &p, QObject *parent)
    : QObject(parent), d_ptr(&p)
{
}

HProtocol::~HProtocol()
{
    close();
}

void HProtocol::initialize(QVariantMap param)
{
    if (param.contains("objectName"))
        setObjectName(param.value("objectName").toString());
    if (param.contains("strategy"))
        setStrategy(static_cast<IProtocolStrategy *>(param.value("strategy").value<void *>()));
}

void HProtocol::setStrategy(IProtocolStrategy *strategy)
{
    close();
    d_ptr->strategy = strategy;
}

HErrorType HProtocol::open()
{
    QMutexLocker locker(d_ptr->mutex);

    if (d_ptr->strategy == nullptr)
        return E_PROTOCOL_STRATEGY_INVALID;
    return d_ptr->strategy->open();
}

HErrorType HProtocol::close()
{
    if (d_ptr->strategy != nullptr)
        d_ptr->strategy->close();
    return E_OK;
}

HErrorType HProtocol::setData(HActionType action, int value, int delay)
{
    QVector<uchar> data;
    data << uchar(value % 256) << uchar(value / 256);
    return setData(action, data, delay);
}

HErrorType HProtocol::setData(HActionType action, double value, double factor, int delay)
{
    return setData(action, int(value * factor), delay);
}

HErrorType HProtocol::setData(HActionType action, uchar value, int delay)
{
    QVector<uchar> data;
    data << value;
    return setData(action, data, delay);
}

HErrorType HProtocol::setData(HActionType action, uint value, int delay)
{
    QVector<uchar> data;
    data.append((value >>  0) & 0xFF);
    data.append((value >>  8) & 0xFF);
    data.append((value >> 16) & 0xFF);
    data.append((value >> 24) & 0xFF);
    return setData(action, data, delay);
}

HErrorType HProtocol::setData(HActionType action, QVector<int> value, int delay)
{
    QVector<uchar> data;
    for (auto i : value)
        data << uchar(i % 256) << uchar(i / 256);
    return setData(action, data, delay);
}

HErrorType HProtocol::setData(HActionType action, QVector<double> value, double factor, int delay)
{
    QVector<uchar> data;
    for (auto d : value)
    {
        int i = int(d * factor);
        data << uchar(i % 256) << uchar(i / 256);
    }
    return setData(action, data, delay);
}

HErrorType HProtocol::setData(HActionType action, QVector<uchar> value, int delay)
{
    return d_ptr->strategy->setData(action, value, delay);
}

HErrorType HProtocol::setData(HActionType action, QVector<uint> value, int delay)
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

HErrorType HProtocol::getData(HActionType action, int &value, int delay)
{
    QVector<uchar> data;
    auto error = getData(action, data, delay);
    if (error != E_OK)
        return error;
    value = data[0] + data[1] * 256;
    return E_OK;
}

HErrorType HProtocol::getData(HActionType action, double &value, double factor, int delay)
{
    QVector<uchar> data;
    auto error = getData(action, data, delay);
    if (error != E_OK)
        return error;
    value = (data[0] + data[1] * 256) * factor;
    return E_OK;
}

HErrorType HProtocol::getData(HActionType action, uchar &value, int delay)
{
    QVector<uchar> data;
    auto error = getData(action, data, delay);
    if (error != E_OK)
        return error;
    value = data[0];
    return E_OK;
}

HErrorType HProtocol::getData(HActionType action, uint &value, int delay)
{
    QVector<uchar> data;
    auto error = getData(action, data, delay);
    if (error != E_OK)
        return error;
    value = data[0] + data[1] * 256 + data[2] * 256 * 256 + data[3] * 256 * 256 * 256;
    return E_OK;
}

HErrorType HProtocol::getData(HActionType action, QVector<int> &value, int delay)
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

HErrorType HProtocol::getData(HActionType action, QVector<double> &value, double factor, int delay)
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

HErrorType HProtocol::getData(HActionType action, QVector<uchar> &value, int delay)
{
    return d_ptr->strategy->getData(action, value, delay);
}

HErrorType HProtocol::getData(HActionType action, QVector<uint> &value, int delay)
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
