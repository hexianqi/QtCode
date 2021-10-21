#include "HAbstractShaderEffect_p.h"

HE_CONTROL_BEGIN_NAMESPACE

HAbstractShaderEffect::HAbstractShaderEffect(QObject *parent) :
    QObject(parent),
    d_ptr(new HAbstractShaderEffectPrivate)
{
}

HAbstractShaderEffect::HAbstractShaderEffect(HAbstractShaderEffectPrivate &p, QObject *parent) :
    QObject(parent),
    d_ptr(&p)
{
}

HAbstractShaderEffect::~HAbstractShaderEffect() = default;

void HAbstractShaderEffect::initialize(QVariantMap /*param*/)
{
}

HE_CONTROL_END_NAMESPACE
