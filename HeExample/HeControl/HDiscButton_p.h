#pragma once

#include "HDiscButton.h"

HE_BEGIN_NAMESPACE

class HDiscButtonPrivate
{
public:
    double circularRadius = 0.0;
    double boardRadius = 0.0;
    QPointF boardCenter = QPointF(0.0, 0.0);
    HDiscButton::ButtonType pressButtonType = HDiscButton::Button_None;
};


HE_END_NAMESPACE


