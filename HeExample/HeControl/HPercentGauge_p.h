#ifndef HPERCENTGAUGE_P_H
#define HPERCENTGAUGE_P_H

#include "HPercentGauge.h"
#include "HAnimationProgress_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HPercentGaugePrivate : public HAnimationProgressPrivate
{
public:
    int scaleMajor = 10;
    int scaleMinor = 5;
    int angleStart = 60;
    int angleEnd = 60;
    QColor background = QColor(0, 0, 0, 0);
    QColor baseColor = QColor(34, 163, 169, 255);
    QColor arcColor = QColor(34, 163, 169, 255);
    QColor scaleColor = QColor(34, 163, 169, 100);
    QColor scaleLabelColor = QColor(34, 163, 169, 200);
    QColor textColor = QColor(34, 163, 169, 255);
    QColor titleColor = QColor(34, 163, 169, 255);
    QString title;
};

HE_CONTROL_END_NAMESPACE

#endif // HPERCENTGAUGE_P_H
