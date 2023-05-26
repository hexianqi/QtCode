#include "HSlDevice1_p.h"
#include "IPort.h"
#include "HeCore/HException.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

HSlDevice1::HSlDevice1(QObject *parent) :
    HAbstractDevice(*new HSlDevice1Private, parent)
{
}

HSlDevice1::HSlDevice1(HSlDevice1Private &p, QObject *parent) :
    HAbstractDevice(p, parent)
{
}

HSlDevice1::~HSlDevice1() = default;

QString HSlDevice1::typeName()
{
    return "HSlDevice1";
}

bool HSlDevice1::setData(HActionType action, QVector<uchar> value, int delay)
{
    Q_D(HSlDevice1);
    auto param = d->actionParams.value(action);
    if (param.size() < 4)
        throw HException(E_DEVICE_ACTION_PARAM_ERROR);

    auto size = value.size() + 3;
    auto downData = QVector<uchar>() << uchar(d->deviceID) << uchar(size % 256) << uchar(size / 256) << param[2] << param[3] << value;
    auto upData = QVector<uchar>(6);

    transport(downData, upData, delay);
    checkData(upData, param[2], param[3]);
    return true;
}

bool HSlDevice1::getData(HActionType action, QVector<uchar> &value, int delay)
{
    Q_D(HSlDevice1);
    auto param = d->actionParams.value(action);
    if (param.size() < 4)
        throw HException(E_DEVICE_ACTION_PARAM_ERROR);

    auto downData =  QVector<uchar>() << (uchar(d->deviceID)) << 0x03 << 0x00 << param[2] << param[3];
    auto upData = QVector<uchar>(6 + param[0] * 256 + param[1]);

    transport(downData, upData, delay);
    checkData(upData, param[2], param[3]);
    value = upData.mid(6);
    return true;
}

bool HSlDevice1::checkData(QVector<uchar> value, uchar cmd1, uchar cmd2)
{
    Q_D(HSlDevice1);
    if (value.size() < 6
        || value[0] != d->deviceID
        || value[3] != cmd1
        || value[4] != cmd2)
        throw HException(E_DEVICE_DATA_RETURN_ERROR);
    if (value[5] != 0x00)
        throw HException(HErrorType(E_DEVICE_FEEDBACK_OK + value[5]));
    return true;
}

HE_END_NAMESPACE
