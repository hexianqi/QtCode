#pragma once
#include "HHueSatPicker.h"

HE_BEGIN_NAMESPACE

class HHueSatPickerPrivate
{
public:
    int minimumHue = 0;
    int maximumHue = 360;
    int minimumSat = 0;
    int maximumSat = 255;
    int value = 255;
    QColor color;
    QPointF pos = QPointF(0.0, 0.0);
    QPixmap pixmap;
};

HE_END_NAMESPACE
