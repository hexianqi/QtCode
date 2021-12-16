#pragma once

#include "HNavLabel.h"

HE_BEGIN_NAMESPACE

class HNavLabelPrivate
{
public:
    int borderRadius = 5;
    QColor background = QColor(100, 184, 255);
    QColor foreground = Qt::white;
    bool showArrow = true;
    int arrowSize = 5;
    HControlType::Position arrowPosition = HControlType::Position_Right;
    bool showTriangle = false;
    int triangleSize = 5;
    HControlType::Position trianglePosition = HControlType::Position_Left;
    QColor triangleColor = Qt::white;
    QRect plotArea;
};

HE_END_NAMESPACE
