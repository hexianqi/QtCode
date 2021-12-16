#include "HAbstractCodec_p.h"

HE_BEGIN_NAMESPACE

HAbstractCodec::HAbstractCodec() :
    d_ptr(new HAbstractCodecPrivate)
{
}

HAbstractCodec::HAbstractCodec(HAbstractCodecPrivate &p) :
    d_ptr(&p)
{
}

HAbstractCodec::~HAbstractCodec() = default;

HE_END_NAMESPACE
