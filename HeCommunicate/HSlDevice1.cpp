#include "HSlDevice1_p.h"
#include "IPort.h"
#include <QtCore/QDebug>

HE_COMMUNICATE_BEGIN_NAMESPACE

HSlDevice1::HSlDevice1() :
    HAbstractDevice(*new HSlDevice1Private)
{
}

HSlDevice1::HSlDevice1(HSlDevice1Private &p) :
    HAbstractDevice(p)
{
}

HSlDevice1::~HSlDevice1()
{
    qDebug() << __func__;
}

QString HSlDevice1::typeName()
{
    return "HSlDevice1";
}

HErrorType HSlDevice1::setData(HActionType action, QVector<uchar> value, int delay)
{
    Q_D(HSlDevice1);
    auto param = d->actionParams.value(action);
    if (param.size() < 4)
        return E_DEVICE_ACTION_PARAM_ERROR;

    auto size = value.size() + 3;
    auto downData = QVector<uchar>() << uchar(d->deviceID) << uchar(size % 256) << uchar(size / 256) << param[2] << param[3] << value;
    auto upData = QVector<uchar>(6);

    auto error = transport(downData, upData, delay);
    if (error != E_OK)
        return error;

    if (upData.size() < 6
            || upData[0] != d->deviceID
            || upData[3] != param[2]
            || upData[4] != param[3])
        return E_DEVICE_DATA_RETURN_ERROR;
    if (upData[5] != 0x00)
        return HErrorType(E_DEVICE_FEEDBACK_OK + upData[5]);
    return E_OK;
}

HErrorType HSlDevice1::getData(HActionType action, QVector<uchar> &value, int delay)
{
    Q_D(HSlDevice1);
    auto param = d->actionParams.value(action);
    if (param.size() < 4)
        return E_DEVICE_ACTION_PARAM_ERROR;

    auto downData =  QVector<uchar>() << (uchar(d->deviceID)) << 0x03 << 0x00 << param[2] << param[3];
    auto upData = QVector<uchar>(6 + param[0] * 256 + param[1]);

    auto error = transport(downData, upData, delay);
    if (error != E_OK)
        return error;

    if (upData.size() < 6
            || upData[0] != d->deviceID
            || upData[3] != param[2]
            || upData[4] != param[3])
        return E_DEVICE_DATA_RETURN_ERROR;
    if (upData[5] != 0x00)
        return HErrorType(E_DEVICE_FEEDBACK_OK + upData[5]);
    value = upData.mid(6);
    return E_OK;
}

HE_COMMUNICATE_END_NAMESPACE
