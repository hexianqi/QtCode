#include "HAbstractCodec_p.h"

HE_BEGIN_NAMESPACE

HAbstractCodec::HAbstractCodec(QObject *parent) :
    QObject(parent),
    d_ptr(new HAbstractCodecPrivate)
{
}

HAbstractCodec::HAbstractCodec(HAbstractCodecPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HAbstractCodec::~HAbstractCodec() = default;

HE_END_NAMESPACE
