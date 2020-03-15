#include "HBigProtocol_p.h"
#include <QtCore/QDebug>

HE_COMMUNICATE_BEGIN_NAMESPACE

HBigProtocol::HBigProtocol() :
    HAbstractProtocol(*new HBigProtocolPrivate)
{
}

HBigProtocol::HBigProtocol(HBigProtocolPrivate &p) :
    HAbstractProtocol(p)
{
}

HBigProtocol::~HBigProtocol()
{
    qDebug() << __func__;
}

QString HBigProtocol::typeName()
{
    return "HBigProtocol";
}

HErrorType HBigProtocol::setData(HActionType action, int value, int delay)
{
    auto data = QVector<uchar>() << uchar(value / 256) << uchar(value % 256);
    return setData(action, data, delay);
}

HErrorType HBigProtocol::setData(HActionType action, uchar value, int delay)
{
    return HAbstractProtocol::setData(action, value, delay);
}

HErrorType HBigProtocol::setData(HActionType action, uint value, int delay)
{
    auto data = QVector<uchar>() << ((value >> 24) & 0xFF)
                                 << ((value >> 16) & 0xFF)
                                 << ((value >>  8) & 0xFF)
                                 << ((value >>  0) & 0xFF);
    return setData(action, data, delay);
}

HErrorType HBigProtocol::setData(HActionType action, QVector<int> value, int delay)
{
    QVector<uchar> data;
    for (auto i : value)
        data << uchar(i / 256) << uchar(i % 256);
    return setData(action, data, delay);
}

HErrorType HBigProtocol::setData(HActionType action, QVector<uchar> value, int delay)
{
    return HAbstractProtocol::setData(action, value, delay);
}

HErrorType HBigProtocol::setData(HActionType action, QVector<uint> value, int delay)
{
    QVector<uchar> data;
    for (auto i : value)
    {
        data << ((i >> 24) & 0xFF)
             << ((i >> 16) & 0xFF)
             << ((i >>  8) & 0xFF)
             << ((i >>  0) & 0xFF);
    }
    return setData(action, data, delay);
}

HErrorType HBigProtocol::getData(HActionType action, int &value, int delay)
{
    QVector<uchar> data;
    auto error = getData(action, data, delay);
    if (error != E_OK)
        return error;
    value = data[0] * 256 + data[1];
    return E_OK;
}

HErrorType HBigProtocol::getData(HActionType action, uchar &value, int delay)
{
    return HAbstractProtocol::getData(action, value, delay);
}

HErrorType HBigProtocol::getData(HActionType action, uint &value, int delay)
{
    QVector<uchar> data;
    auto error = getData(action, data, delay);
    if (error != E_OK)
        return error;
    value = uint((data[0] << 24) + (data[1] << 16) + (data[2] << 8) + data[3]);
    return E_OK;
}

HErrorType HBigProtocol::getData(HActionType action, QVector<int> &value, int delay)
{
    QVector<uchar> data;
    auto error = getData(action, data, delay);
    if (error != E_OK)
        return error;
    if (value.size() == 0)
        value.resize(data.size() / 2);
    auto size = qMin(value.size(), data.size() / 2);
    for (int i = 0; i < size; i++)
        value[i] = data[2 * i] * 256 + data[2 * i + 1];
    return E_OK;
}

HErrorType HBigProtocol::getData(HActionType action, QVector<uchar> &value, int delay)
{
    return HAbstractProtocol::getData(action, value, delay);;
}

HErrorType HBigProtocol::getData(HActionType action, QVector<uint> &value, int delay)
{
    QVector<uchar> data;
    auto error = getData(action, data, delay);
    if (error != E_OK)
        return error;
    if (value.size() == 0)
        value.resize(data.size() / 4);
    auto size = qMin(value.size(), data.size() / 4);
    for (int i = 0; i < size; i++)
        value[i] = uint((data[4 * i] << 24) + (data[4 * i + 1] << 16) + (data[4 * i + 2] << 8) + data[4 * i + 3]);
    return E_OK;
}

HErrorType HBigProtocol::getData(HActionType action, QVector<double> &value, int delay)
{
    QVector<uchar> data;
    auto error = getData(action, data, delay);
    if (error != E_OK)
        return error;
    if (value.size() == 0)
        value.resize(data.size() / 2);
    auto size = qMin(value.size(), data.size() / 2);
    for (int i = 0; i < size; i++)
        value[i] = data[2 * i] * 256 + data[2 * i + 1];
    return E_OK;
}

HE_COMMUNICATE_END_NAMESPACE
