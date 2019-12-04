#include "HPowerFactorDevice_p.h"
#include "IPort.h"
#include <QtCore/QDebug>

HE_COMMUNICATE_BEGIN_NAMESPACE

HPowerFactorDevice::HPowerFactorDevice() :
    HAbstractDevice(*new HPowerFactorDevicePrivate)
{
}

HPowerFactorDevice::~HPowerFactorDevice()
{
    qDebug() << __func__;
}

QString HPowerFactorDevice::typeName()
{
    return "HPowerFactorDevice";
}

HErrorType HPowerFactorDevice::setData(HActionType /*action*/, QVector<uchar> /*value*/, int /*delay*/)
{
    return E_OK;
}

HErrorType HPowerFactorDevice::getData(HActionType action, QVector<uchar> &value, int /*delay*/)
{
    Q_D(HPowerFactorDevice);
    auto param = d->actionParams.value(action);
    if (param.size() < 3)
        return E_DEVICE_ACTION_PARAM_ERROR;

    auto upData = QVector<uchar>(param[0] * 256 + param[1]);
    auto downData =  QVector<uchar>() << param[2];
    auto error = transport(downData, upData, 200);
    if (error != E_OK)
        return error;
    value = upData;
    return E_OK;
}

HErrorType HPowerFactorDevice::transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay)
{
    Q_D(HPowerFactorDevice);
    return d->port->transport(downData, upData, delay);
}

HE_COMMUNICATE_END_NAMESPACE
