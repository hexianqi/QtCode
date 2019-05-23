#include "HSlDevice2_p.h"
#include "IPort.h"
#include <QtCore/QVector>
#include <QtCore/QtMath>

HE_COMMUNICATE_BEGIN_NAMESPACE

HSlDevice2::HSlDevice2() :
    HAbstractDevice(*new HSlDevice2Private)
{
}

HSlDevice2::HSlDevice2(HSlDevice2Private &p) :
    HAbstractDevice(p)
{
}

HSlDevice2::~HSlDevice2()
{
}

QString HSlDevice2::typeName()
{
    return "HSlDevice2";
}

HErrorType HSlDevice2::setData(HActionType action, QVector<uchar> value, int delay)
{
    Q_D(HSlDevice2);
    auto param = d->actionParams.value(action);
    if (param.size() < 3)
        return E_DEVICE_ACTION_PARAM_ERROR;
    if (param[0] == 0xFF)
        return setDataBatch(param, value, delay);
    return setData(param[2], value, delay);
}

HErrorType HSlDevice2::getData(HActionType action, QVector<uchar> &value, int delay)
{
    Q_D(HSlDevice2);
    auto param = d->actionParams.value(action);
    if (param.size() < 3)
        return E_DEVICE_ACTION_PARAM_ERROR;
    if (param[0] == 0xFF)
        return getDataBatch(param, value, delay);
    return getData(param[0] * 256 + param[1] + 4, param[2], 0, value, delay);
}

HErrorType HSlDevice2::setData(uchar cmd, QVector<uchar> value, int delay)
{
    if (value.size() % 2 == 0)
        value.append(0);
    auto size = value.size() + 3;
    auto downData = QVector<uchar>() << uchar(size / 256) << uchar(size % 256) << cmd << value;
    auto upData = QVector<uchar>(4);
    auto error = transport(downData, upData, delay);
    if (error != E_OK)
        return error;
    if (upData.size() < 4 || upData[0] != 0x00 || upData[1] != 0x04 || upData[2] != cmd)
        return E_DEVICE_DATA_RETURN_ERROR;
    return E_OK;
}

HErrorType HSlDevice2::getData(int size, uchar cmd, uchar block, QVector<uchar> &value, int delay)
{
    auto downData = QVector<uchar>() << 0x00 << 0x04 << cmd << block;
    auto upData = QVector<uchar>(size);
    auto error = transport(downData, upData, delay);
    if (error != E_OK)
        return error;
    if (upData.size() < 4 || upData[0] != size / 256 || upData[1] != size % 256 || upData[2] != cmd)
        return E_DEVICE_DATA_RETURN_ERROR;
    value = upData.mid(4);
    return E_OK;
}

HErrorType HSlDevice2::setDataBatch(QList<uchar> param, QVector<uchar> value, int delay)
{
    if (value.size() < 2)
        return E_DEVICE_DATA_SEND_ERROR;

    int i,n;
    for (i = value.size() % param[1]; i != 0 && i < param[1]; i++)
        value.append(0);
    n = value.size() / param[1];
    for (i = 0; i < n; i++)
    {
        auto buff = QVector<uchar>() << uchar(i + 1) << value.mid(i * param[1], param[1]);
        auto error = setData(param[2], buff, delay);
        if (error != E_OK)
            return error;
    }
    return E_OK;
}

HErrorType HSlDevice2::getDataBatch(QList<uchar> param, QVector<uchar> &value, int delay)
{
    QVector<uchar> buff;
    int size = param[1] + 4;
    auto error = getData(size, param[2], 1, buff, delay);
    if (error != E_OK)
        return error;
    value << buff;

    int n = qCeil(value[0] * 256.0 + value[1] / param[1]);
    for (int i = 1; i < n; i++)
    {
        error = getData(size, param[2], i + 1, buff, delay);
        if (error != E_OK)
            return error;
        value << buff;
    }
    return E_OK;
}

HErrorType HSlDevice2::transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay)
{
    Q_D(HSlDevice2);
    return d->port->transport(downData, upData, delay);
}

HE_COMMUNICATE_END_NAMESPACE
