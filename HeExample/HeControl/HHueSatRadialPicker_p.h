#pragma once

#include "HHueSatRadialPicker.h"

HE_BEGIN_NAMESPACE

class HHueSatRadialPickerPrivate
{
public:
    int value = 255;
    QColor color;
    QConicalGradient conicalGradient;
    QRadialGradient radialGradient;
    QPixmap boardPixmap;
    double boardRadius = 0.0;
    QPointF boardCenter = QPointF(0.0, 0.0);
    QPointF pos = QPointF(0.0, 0.0);
};

HE_END_NAMESPACE
