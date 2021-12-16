#pragma once

#include "HMiniGauge.h"
#include "HCircleGauge_p.h"

HE_BEGIN_NAMESPACE

class HMiniGaugePrivate : public HCircleGaugePrivate
{
public:
    HMiniGaugePrivate();

public:
    HControlType::PointerStyle pointerStyle = HControlType::PointerStyle_Circle;
    QColor borderColor = Qt::black;
    QColor progressColor = QColor(100, 184, 255);
    bool doubleProgress = true;
    bool showValue = true;
    bool pressed = false;
};

HE_END_NAMESPACE
