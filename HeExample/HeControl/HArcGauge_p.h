#ifndef HARCGAUGE_P_H
#define HARCGAUGE_P_H

#include "HArcGauge.h"
#include "HAnimationProgress_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HArcGaugePrivate : public HAnimationProgressPrivate
{
public:
    int scaleMajor = 10;
    int scaleMinor = 10;
    int angleStart = 45;
    int angleEnd = 45;
    QColor arcColor = QColor(50, 50, 50);
    QColor scaleColor = QColor(60, 60, 60);
    QColor scaleLabelColor = QColor(20, 20, 20);
    QColor textColor = QColor(100, 184, 255);
    QColor pointerColor = QColor(255, 107, 107);
    HArcGauge::PointerStyle pointerStyle = HArcGauge::Circle;
};

HE_CONTROL_END_NAMESPACE

#endif // HARCGAUGE_P_H
