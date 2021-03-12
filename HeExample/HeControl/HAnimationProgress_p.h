#pragma once

#include "HAnimationProgress.h"
#include "HAbstractProgress_p.h"

class QPropertyAnimation;

HE_CONTROL_BEGIN_NAMESPACE

class HAnimationProgressPrivate : public HAbstractProgressPrivate
{
public:
    bool animationEnable = true;
    double currentValue = 0;
    QPropertyAnimation *animation = nullptr;
};

HE_CONTROL_END_NAMESPACE
