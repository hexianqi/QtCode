#ifndef HSPLITEFFECT_P_H
#define HSPLITEFFECT_P_H

#include "HSplitEffect.h"
#include "HAbstractShaderEffect_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HSplitEffectPrivate : public HAbstractShaderEffectPrivate
{
public:
    Qt::Orientation orientation = Qt::Horizontal;
    HSplitEffect::SplitStyle splitStyle = HSplitEffect::SplitStyle_OutsideToInside;
};

HE_CONTROL_END_NAMESPACE

#endif // HSPLITEFFECT_P_H
