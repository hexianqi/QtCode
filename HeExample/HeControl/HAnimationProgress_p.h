#ifndef HANIMATIONPROGRESS_P_H
#define HANIMATIONPROGRESS_P_H

#include "HAnimationProgress.h"
#include "HAbstractProgress_p.h"

class QPropertyAnimation;

HE_CONTROL_BEGIN_NAMESPACE

class HAnimationProgressPrivate : public HAbstractProgressPrivate
{
public:
    bool animationEnable = true;
    double currentValue = 0;

public:
    QPropertyAnimation *animation = nullptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HANIMATIONPROGRESS_P_H
