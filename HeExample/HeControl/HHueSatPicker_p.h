#pragma once
#include "HHueSatPicker.h"

HE_CONTROL_BEGIN_NAMESPACE

class HHueSatPickerPrivate
{
public:
    int minimumHue = 0;
    int maximumHue = 359;
    int minimumSat = 0;
    int maximumSat = 255;
    int value = 255;
    QColor color;
    QPointF point = QPointF(0.0, 0.0);
    QPixmap pixmap;
};

HE_CONTROL_END_NAMESPACE
