#pragma once

#include "HColorGradientRoundedButton.h"

class QPropertyAnimation;

HE_BEGIN_NAMESPACE

class HColorGradientRoundedButtonPrivate
{
public:
    HDoubleColor currentColor;
    HDoubleColor startColor;
    HDoubleColor endColor;
    QPropertyAnimation *animation = nullptr;
};

HE_END_NAMESPACE
