#include "HAbstractCodec_p.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

HAbstractCodec::HAbstractCodec() :
    d_ptr(new HAbstractCodecPrivate)
{
}

HAbstractCodec::~HAbstractCodec() = default;

HAbstractCodec::HAbstractCodec(HAbstractCodecPrivate &p) :
    d_ptr(&p)
{
}

HE_COMMUNICATE_END_NAMESPACE
