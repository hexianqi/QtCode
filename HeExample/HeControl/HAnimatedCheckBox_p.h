#pragma once

#include "HAnimatedCheckBox.h"

class QLabel;
class QPropertyAnimation;

HE_BEGIN_NAMESPACE

class HAnimatedCheckBoxPrivate
{
public:
    QLabel *indicator;
    QPropertyAnimation *animation;
};

HE_END_NAMESPACE
