#ifndef HHUESATRADIALPICKER_P_H
#define HHUESATRADIALPICKER_P_H

#include "HHueSatRadialPicker.h"

HE_CONTROL_BEGIN_NAMESPACE

class HHueSatRadialPickerPrivate
{
public:
    int value = 255;
    QColor color;
    QPointF point = QPointF(0.0, 0.0);
    QPixmap pixmap;
    QConicalGradient gradient;
};

HE_CONTROL_END_NAMESPACE

#endif // HHUESATRADIALPICKER_P_H
