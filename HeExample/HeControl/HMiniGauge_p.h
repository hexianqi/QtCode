#ifndef HMINIGAUGE_P_H
#define HMINIGAUGE_P_H

#include "HMiniGauge.h"
#include "HCircleGauge_p.h"

HE_CONTROL_BEGIN_NAMESPACE

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

HE_CONTROL_END_NAMESPACE

#endif // HMINIGAUGE_P_H
