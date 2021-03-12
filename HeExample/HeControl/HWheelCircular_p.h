#pragma once

#include "HWheelCircular.h"
#include "HAbstractCircular_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HWheelCircularPrivate : public HAbstractCircularPrivate
{
public:
    QColor backgroundStart = QColor(65, 65, 65);
    QColor backgroundEnd = QColor(89, 89, 89);
    QColor foreground1Start = QColor(0, 133, 203);
    QColor foreground1End = QColor(0, 118, 177);
    QColor foreground2Start = QColor(255, 255, 255);
    QColor foreground2End = QColor(233, 233, 233);
};

HE_CONTROL_END_NAMESPACE
