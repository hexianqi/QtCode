#ifndef HCIRCLEGAUGE_P_H
#define HCIRCLEGAUGE_P_H

#include "HCircleGauge.h"
#include "HAnimationProgress_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HCircleGaugePrivate : public HAnimationProgressPrivate
{
public:
    int scaleMajor = 10;
    int scaleMinor = 5;
    int scaleDecimal = 0;
    int angleStart = 50;
    int angleEnd = 50;
    QColor background = Qt::transparent;
    QColor textColor = QColor(50, 50, 50);
    QColor pointerColor = QColor(178, 221, 253);
    QColor scaleColor = QColor(60, 60, 60);
    QColor scaleLabelColor = QColor(20, 20, 20);
};

HE_CONTROL_END_NAMESPACE

#endif // HCIRCLEGAUGE_P_H
