#include "HAbstractShaderEffect_p.h"

HE_CONTROL_BEGIN_NAMESPACE

HAbstractShaderEffect::HAbstractShaderEffect(QObject *parent) :
    IShaderEffect(parent),
    d_ptr(new HAbstractShaderEffectPrivate)
{
}

HAbstractShaderEffect::HAbstractShaderEffect(HAbstractShaderEffectPrivate &p, QObject *parent) :
    IShaderEffect(parent),
    d_ptr(&p)
{
}

HAbstractShaderEffect::~HAbstractShaderEffect() = default;

HE_CONTROL_END_NAMESPACE
