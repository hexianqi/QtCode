#pragma once

#include "HMoveEffect.h"
#include "HAbstractShaderEffect_p.h"

HE_BEGIN_NAMESPACE

class HMoveEffectPrivate : public HAbstractShaderEffectPrivate
{
public:
    HControlType::Direction4 direction = HControlType::Direction4_Left;
};

HE_END_NAMESPACE
