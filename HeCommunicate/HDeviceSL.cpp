#include "HDeviceSL_p.h"
#include "IPort.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

HDeviceSL::HDeviceSL() :
    HAbstractDevice(*new HDeviceSLPrivate)
{
}

HDeviceSL::HDeviceSL(HDeviceSLPrivate &p) :
    HAbstractDevice(p)
{
}

HDeviceSL::~HDeviceSL()
{
}

QString HDeviceSL::typeName()
{
    return "HDeviceSL";
}

HErrorType HDeviceSL::setData(HActionType action, QVector<uchar> value, int delay)
{
    Q_D(HDeviceSL);
    auto param = d->actionParam.value(action);
    if (param.size() < 4)
        return E_DEVICE_ACTION_ERROR;

    QVector<uchar> downData, upData;
    int size = value.size() + 3;
    downData << uchar(d->deviceID) << uchar(size % 256) << uchar(size / 256) << param[2] << param[3];
    downData << value;
    upData.resize(6);

    auto error = transport(downData, upData, delay);
    if (error != E_OK)
        return error;

    if (upData.size() < 6 || upData[0] != d->deviceID || upData[3] != param[2] || upData[4] != param[3])
        return E_DEVICE_RETURN_DATA_ERROR;
    if (upData[5] != 0x00)
        return HErrorType(E_DEVICE_FEEDBACK_OK + upData[5]);
    return E_OK;
}

HErrorType HDeviceSL::getData(HActionType action, QVector<uchar> &value, int delay)
{
    Q_D(HDeviceSL);
    auto param = d->actionParam.value(action);
    if (param.size() < 4)
        return E_DEVICE_ACTION_ERROR;

    QVector<uchar> downData, upData;
    downData << (uchar(d->deviceID)) << 0x03 << 0x00 << param[2] << param[3];
    upData.resize(6 + param[0] * 256 + param[1]);

    auto error = transport(downData, upData, delay);
    if (error != E_OK)
        return error;

    if (upData.size() < 6 || upData[0] != d->deviceID || upData[3] != param[2] || upData[4] != param[3])
        return E_DEVICE_RETURN_DATA_ERROR;
    if (upData[5] != 0x00)
        return HErrorType(E_DEVICE_FEEDBACK_OK + upData[5]);
    value = upData.mid(6);
    return E_OK;
}

HErrorType HDeviceSL::transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay)
{
    Q_D(HDeviceSL);
    return d->port->transport(downData, upData, delay);
}

HE_COMMUNICATE_END_NAMESPACE

