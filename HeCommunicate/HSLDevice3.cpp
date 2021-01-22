#include "HSlDevice3_p.h"
#include "HSlCodec.h"
#include "HeCore/HException.h"
#include <QtCore/QDebug>

HE_COMMUNICATE_BEGIN_NAMESPACE

HSlDevice3Private::HSlDevice3Private()
{
    codec = QSharedPointer<ICodec>(new HSlCodec);
}

HSlDevice3::HSlDevice3() :
    HSlDevice1(*new HSlDevice3Private)
{
}

HSlDevice3::~HSlDevice3()
{
    qDebug() << __func__;
}

void HSlDevice3::initialize(QVariantMap param)
{
    Q_D(HSlDevice3);
    HSlDevice1::initialize(param);
    d->codec->initialize(param);
}

QString HSlDevice3::typeName()
{
    return "HSlDevice3";
}

void HSlDevice3::transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay)
{
    Q_D(HSlDevice3);

    auto upData2 = d->codec->preDecode(upData);
    auto downData2 = d->codec->encode(downData);
    HSlDevice1::transport(downData2, upData2, delay);
    if (!d->codec->check(upData2))
        throw HException(E_DEVICE_CHECKCODE_ERROR);
    upData = d->codec->decode(upData2);
}

HE_COMMUNICATE_END_NAMESPACE
