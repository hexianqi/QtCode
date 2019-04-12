#include "HDeviceSLCodec_p.h"
#include "HCodecSL.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

HDeviceSLCodecPrivate::HDeviceSLCodecPrivate()
{
    codec = new HCodecSL;
}

HDeviceSLCodec::HDeviceSLCodec() :
    HDeviceSL(*new HDeviceSLCodecPrivate)
{
}

HDeviceSLCodec::~HDeviceSLCodec()
{
}

void HDeviceSLCodec::initialize(QVariantMap param)
{
    Q_D(HDeviceSLCodec);
    HDeviceSL::initialize(param);
    d->codec->initialize(param);
}

QString HDeviceSLCodec::typeName()
{
    return "HDeviceSLCodec";
}

HErrorType HDeviceSLCodec::transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay)
{
    Q_D(HDeviceSLCodec);

    auto upData2 = d->codec->preDecode(upData);
    auto downData2 = d->codec->encode(downData);
    auto error = HDeviceSL::transport(downData2, upData2, delay);
    if (error != E_OK)
        return error;
    if (!d->codec->check(upData2))
        return E_DEVICE_CHECKCODE_ERROR;
    upData = d->codec->decode(upData2);
    return E_OK;
}

HE_COMMUNICATE_END_NAMESPACE
