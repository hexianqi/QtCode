#pragma once

#include "HBlindsEffect.h"
#include "HAbstractShaderEffect_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HBlindsEffectPrivate : public HAbstractShaderEffectPrivate
{
public:
    int page = 10;
    HControlType::Direction4 direction = HControlType::Direction4_Down;
};

HE_CONTROL_END_NAMESPACE
