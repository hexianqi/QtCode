#ifndef HKNOBGAUGE_P_H
#define HKNOBGAUGE_P_H

#include "HKnobGauge.h"
#include "HAnimationProgress_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HKnobGaugePrivate : public HAnimationProgressPrivate
{
public:
    int angleStart = 0;
    int angleEnd = 0;
    QColor background = QColor(30, 30, 30);
    QColor progressBackground = QColor(50, 50, 50);
    QColor progressColor = QColor(100, 184, 255);
    QColor circleColorStart = QColor(80, 80, 80);
    QColor circleColorEnd = QColor(50, 50, 50);
    QColor textColor = QColor(200, 200, 200);
    bool showPointer = true;
    bool showValue = false;
    HKnobGauge::PointerStyle pointerStyle = HKnobGauge::Circle;

    bool pressed = false;
    bool hover = false;
    int radiusCoverCircle = 85;
    int radiusCircle = 80;
    QPropertyAnimation *animationHover = nullptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HKNOBGAUGE_P_H
