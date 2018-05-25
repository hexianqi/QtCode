#include "HDeviceSL_p.h"
#include "IPort.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

HDeviceSLPrivate::HDeviceSLPrivate()
{
    encrypts << false;
    checkCodes << false;
}

void HDeviceSLPrivate::setEncrypt(QVector<bool> value)
{
    encrypts = value;
    if (encrypts.size() == 0)
        encrypts.append(false);
}

void HDeviceSLPrivate::setCheckCode(QVector<bool> value)
{
    checkCodes = value;
    if (checkCodes.size() == 0)
        checkCodes.append(false);
}

bool HDeviceSLPrivate::isEncrypt(int n)
{
    n = qBound(0, n, encrypts.size() - 1);
    return encrypts[n];
}

bool HDeviceSLPrivate::isCheckCode(int n)
{
    n = qBound(0, n, checkCodes.size() - 1);
    return checkCodes[n];
}

HDeviceSL::HDeviceSL()
    : HAbstractDevice(*new HDeviceSLPrivate)
{
}

HDeviceSL::HDeviceSL(HDeviceSLPrivate &p)
    : HAbstractDevice(p)
{
}

HDeviceSL::~HDeviceSL()
{
}

void HDeviceSL::initialize(QVariantMap param)
{
    Q_D(HDeviceSL);
    HAbstractDevice::initialize(param);
    if (param.contains("encrypt"))
        d->setEncrypt(param.value("encrypt").value<QVector<bool>>());
    if (param.contains("checkCode"))
        d->setCheckCode(param.value("checkCode").value<QVector<bool>>());
}

QString HDeviceSL::typeName()
{
    return "HDeviceSL";
}

void HDeviceSL::setEncrypt(QVector<bool> value)
{
    Q_D(HDeviceSL);
    d->setEncrypt(value);
}

void HDeviceSL::setCheckCode(QVector<bool> value)
{
    Q_D(HDeviceSL);
    d->setCheckCode(value);
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
    upData.resize(6);

    auto error = transport(downData, upData, delay);
    if (error != E_OK)
        return error;

    if (upData.size() < 6
            || upData[0] != d->deviceID
            || upData[3] != param[2]
            || upData[4] != param[3])
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

    if (upData.size() < 6
            || upData[0] != d->deviceID
            || upData[3] != param[2]
            || upData[4] != param[3])
        return E_DEVICE_RETURN_DATA_ERROR;
    if (upData[5] != 0x00)
        return HErrorType(E_DEVICE_FEEDBACK_OK + upData[5]);
    value = upData.mid(6);
    return E_OK;
}

HErrorType HDeviceSL::transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay)
{
    Q_D(HDeviceSL);
    int n = 0;
    HErrorType error;
    QVector<uchar> downDataE, upDataE;

    //    n = d->isEncrypt(0) ? qCeil((downData.size()) / 7.0) : 0;
    downDataE = d->isEncrypt(0) ? encrypt(downData, 2) : downData;
    if (d->isCheckCode(0))
        downDataE << calcCode(downDataE);

    n = 0;
    if (d->isEncrypt(1))
        n += 2;
    if (d->isCheckCode(1))
        n += 1;
    upDataE.resize(upData.size() + n);

    error = d->port->transport(downDataE, upDataE, delay);
    if (error != E_OK)
        return error;

    if (d->isCheckCode(1))
    {
        auto code = upDataE.takeLast();
        if (!checkCode(upDataE, code))
            return E_DEVICE_CHECKCODE_ERROR;
    }
    upData = d->isEncrypt(1) ? decrypt(upDataE, 2) : upDataE;
    return E_OK;
}

QVector<uchar> HDeviceSL::encrypt(QVector<uchar> value, int size)
{
    int n = value.size();
    QVector<uchar> result(n + size);

    for (int i = 0; i < n; i++)
    {
        result[i] = (i == 0) ? value[i] | 0x80 : value[i] & 0x7F;
        result[n + i / 7] |= (value[i] & 0x80) >> (7 - (i % 7));
    }
    return result;
}

QVector<uchar> HDeviceSL::decrypt(QVector<uchar> value, int size)
{
    int n = value.size() - size;
    QVector<uchar> result(n);

    for (int i = 0; i < n; i++)
    {
        if ((value[n + i / 7] >> (i % 7)) % 2 == 0)
            result[i] = value[i] & 0x7F;
        else
            result[i] = value[i] | 0x80;
    }
    return result;
}

uchar HDeviceSL::calcCode(QVector<uchar> value)
{
    uint sum = 0;
    for (auto i : value)
        sum += i;
    return sum % 128;
}

bool HDeviceSL::checkCode(QVector<uchar> value, uchar code)
{
    uint sum = 0;
    for (auto i : value)
        sum += i;
    return code == sum % 128;
}

HE_COMMUNICATE_END_NAMESPACE
