#pragma once
#include "HPercentGauge.h"
#include "HCircleGauge_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HPercentGaugePrivate : public HCircleGaugePrivate
{
public:
    HPercentGaugePrivate();

public:
    QColor baseColor = QColor(34, 163, 169, 255);
    QColor arcColor = QColor(34, 163, 169, 255);
    QColor titleColor = QColor(34, 163, 169, 255);
    QString title;
};

HE_CONTROL_END_NAMESPACE
