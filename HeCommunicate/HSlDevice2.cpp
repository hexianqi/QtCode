#include "HSlDevice2_p.h"
#include "IPort.h"
#include "HeCore/HException.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

HSlDevice2::HSlDevice2(QObject *parent) :
    HAbstractDevice(*new HSlDevice2Private, parent)
{
}

HSlDevice2::HSlDevice2(HSlDevice2Private &p, QObject *parent) :
    HAbstractDevice(p, parent)
{
}

HSlDevice2::~HSlDevice2() = default;

QString HSlDevice2::typeName()
{
    return "HSlDevice2";
}

bool HSlDevice2::setData(HActionType action, QVector<uchar> value, int delay)
{
    Q_D(HSlDevice2);
    auto param = d->actionParams.value(action);
    if (param.size() < 3)
        throw HException(E_DEVICE_ACTION_PARAM_ERROR);
    if (param[0] == 0xFF)
        return setDataBatch(param, value, delay);
    return setDataOnce(param[2], value, delay);
}

bool HSlDevice2::getData(HActionType action, QVector<uchar> &value, int delay)
{
    Q_D(HSlDevice2);
    auto param = d->actionParams.value(action);
    if (param.size() < 3)
        throw HException(E_DEVICE_ACTION_PARAM_ERROR);
    if (param[0] == 0xFF)
        return getDataBatch(param, value, delay);
    return getDataOnce(param[0] * 256 + param[1] + 4, param[2], 0, value, delay);
}

bool HSlDevice2::setDataOnce(uchar cmd, QVector<uchar> value, int delay)
{
    if (value.size() % 2 == 0)
        value.append(0);
    auto size = value.size() + 3;
    auto downData = QVector<uchar>() << uchar(size / 256) << uchar(size % 256) << cmd << value;
    auto upData = QVector<uchar>(4);

    transport(downData, upData, delay);

    if (upData.size() < 4
            || upData[0] != 0x00
            || upData[1] != 0x04
            || upData[2] != cmd)
        throw HException(E_DEVICE_DATA_RETURN_ERROR);
    return true;
}

bool HSlDevice2::getDataOnce(int size, uchar cmd, uchar block, QVector<uchar> &value, int delay)
{
    auto downData = QVector<uchar>() << 0x00 << 0x04 << cmd << block;
    auto upData = QVector<uchar>(size);

    transport(downData, upData, delay);

    if (upData.size() < 4
            || upData[0] != size / 256
            || upData[1] != size % 256
            || upData[2] != cmd)
        throw HException(E_DEVICE_DATA_RETURN_ERROR);
    value = upData.mid(4);
    return true;
}

bool HSlDevice2::setDataBatch(QList<uchar> param, QVector<uchar> value, int /*delay*/)
{
    if (value.size() < 2)
        throw HException(E_DEVICE_DATA_SEND_ERROR);

    int i,n;
    for (i = value.size() % param[1]; i != 0 && i < param[1]; i++)
        value.append(0);
    n = value.size() / param[1];
    for (i = 0; i < n; i++)
    {
        auto buff = QVector<uchar>() << uchar(i + 1) << value.mid(i * param[1], param[1]);
        setDataOnce(param[2], buff, 300);
    }
    return true;
}

bool HSlDevice2::getDataBatch(QList<uchar> param, QVector<uchar> &value, int delay)
{
    QVector<uchar> buff;
    int size = param[1] + 4;

    value.clear();
    getDataOnce(size, param[2], 1, buff, delay);
    value << buff;

    auto n = uchar(ceil((value[0] * 256.0 + value[1]) / param[1]));
    for (uchar i = 1; i < n; i++)
    {
        getDataOnce(size, param[2], i + 1, buff, 300);
        value << buff;
    }
    return E_OK;
}

HE_END_NAMESPACE
