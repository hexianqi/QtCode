#include "HPowerFactorDevice_p.h"
#include "IPort.h"
#include "HeCore/HException.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

HPowerFactorDevice::HPowerFactorDevice(QObject *parent) :
    HAbstractDevice(*new HPowerFactorDevicePrivate, parent)
{
}

HPowerFactorDevice::~HPowerFactorDevice() = default;

QString HPowerFactorDevice::typeName()
{
    return "HPowerFactorDevice";
}

bool HPowerFactorDevice::setData(HActionType /*action*/, QVector<uchar> /*value*/, int /*delay*/)
{
    return true;
}

bool HPowerFactorDevice::getData(HActionType action, QVector<uchar> &value, int /*delay*/)
{
    Q_D(HPowerFactorDevice);
    auto param = d->actionParams.value(action);
    if (param.size() < 3)
        throw HException(E_DEVICE_ACTION_PARAM_ERROR);

    auto upData = QVector<uchar>(param[0] * 256 + param[1]);
    auto downData =  QVector<uchar>() << param[2];
    transport(downData, upData, 200);
    value = upData;
    return true;
}

HE_END_NAMESPACE
