#ifndef HMOVEEFFECT_P_H
#define HMOVEEFFECT_P_H

#include "HMoveEffect.h"
#include "HAbstractShaderEffect_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HMoveEffectPrivate : public HAbstractShaderEffectPrivate
{
public:
    HControlType::Direction4 direction = HControlType::Direction4_Left;
};

HE_CONTROL_END_NAMESPACE

#endif // HMOVEEFFECT_P_H
