#pragma once

#include "HHueSatRadialPicker.h"

HE_CONTROL_BEGIN_NAMESPACE

class HHueSatRadialPickerPrivate
{
public:
    int value = 255;
    QColor color;
    QPointF point = QPointF(0.0, 0.0);
    QPixmap pixmap;
    QConicalGradient conicalGradient;
    QRadialGradient radialGradient;
};

HE_CONTROL_END_NAMESPACE
