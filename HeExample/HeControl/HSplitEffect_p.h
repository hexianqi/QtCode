#pragma once

#include "HSplitEffect.h"
#include "HAbstractShaderEffect_p.h"

HE_BEGIN_NAMESPACE

class HSplitEffectPrivate : public HAbstractShaderEffectPrivate
{
public:
    Qt::Orientation orientation = Qt::Horizontal;
    HSplitEffect::SplitStyle splitStyle = HSplitEffect::SplitStyle_OutsideToInside;
};

HE_END_NAMESPACE
