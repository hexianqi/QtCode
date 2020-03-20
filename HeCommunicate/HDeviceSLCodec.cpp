#include "HSlCodecDevice_p.h"
#include "HSlCodec.h"
#include <QtCore/QDebug>

HE_COMMUNICATE_BEGIN_NAMESPACE

HSlCodecDevicePrivate::HSlCodecDevicePrivate()
{
    codec = QSharedPointer<ICodec>(new HSlCodec);
}

HSlCodecDevice::HSlCodecDevice() :
    HSlDevice(*new HSlCodecDevicePrivate)
{
}

HSlCodecDevice::~HSlCodecDevice()
{
    qDebug() << __func__;
}

void HSlCodecDevice::initialize(QVariantMap param)
{
    Q_D(HSlCodecDevice);
    HSlDevice::initialize(param);
    d->codec->initialize(param);
}

QString HSlCodecDevice::typeName()
{
    return "HSlCodecDevice";
}

HErrorType HSlCodecDevice::transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay)
{
    Q_D(HSlCodecDevice);

    auto upData2 = d->codec->preDecode(upData);
    auto downData2 = d->codec->encode(downData);
    auto error = HSlDevice::transport(downData2, upData2, delay);
    if (error != E_OK)
        return error;
    if (!d->codec->check(upData2))
        return E_DEVICE_CHECKCODE_ERROR;
    upData = d->codec->decode(upData2);
    return E_OK;
}

HE_COMMUNICATE_END_NAMESPACE
