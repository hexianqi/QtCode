#ifndef HNAVLABEL_P_H
#define HNAVLABEL_P_H

#include "HNavLabel.h"

HE_CONTROL_BEGIN_NAMESPACE

class HNavLabelPrivate
{
public:
    int borderRadius = 5;
    QColor background = QColor(100, 184, 255);
    QColor foreground = Qt::white;
    bool showArrow = true;
    int arrowSize = 5;
    HNavLabel::Position arrowPosition = HNavLabel::Position_Right;
    bool showTriangle = false;
    int triangleSize = 5;
    HNavLabel::Position trianglePosition = HNavLabel::Position_Left;
    QColor triangleColor = Qt::white;
    QRect plotArea;
};

HE_CONTROL_END_NAMESPACE

#endif // HNAVLABEL_P_H
