#include "HAbstractCodec_p.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

HAbstractCodec::HAbstractCodec() :
    d_ptr(new HAbstractCodecPrivate)
{
}

HAbstractCodec::HAbstractCodec(HAbstractCodecPrivate &p) :
    d_ptr(&p)
{
}

HAbstractCodec::~HAbstractCodec()
{

}

HE_COMMUNICATE_END_NAMESPACE
