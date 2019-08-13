#ifndef HFLIPEFFECT_P_H
#define HFLIPEFFECT_P_H

#include "HFlipEffect.h"
#include "HAbstractShaderEffect_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HFlipEffectPrivate : public HAbstractShaderEffectPrivate
{
public:
    HControlType::Direction4 direction = HControlType::Direction4_Left;
};

HE_CONTROL_END_NAMESPACE

#endif // HFLIPEFFECT_P_H
