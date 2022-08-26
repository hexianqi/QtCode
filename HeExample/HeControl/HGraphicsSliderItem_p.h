#pragma once

#include "HGraphicsSliderItem.h"
#include "HGraphicsObject_p.h"

HE_BEGIN_NAMESPACE

class HGraphicsSliderItemPrivate : public HGraphicsObjectPrivate
{
public:
    HGraphicsSliderItemPrivate(Qt::Orientation);

public:
    Qt::Orientation orientation;
    int minValue = 0;
    int maxValue = 100;
    int nowValue = 50;
    QRectF sliderRect;
    bool slidePressed = false;
    bool inSliderRect = false;
};

HE_END_NAMESPACE

