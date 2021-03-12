#pragma once

#include "HPanelGauge.h"
#include "HCircleGauge_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HPanelGaugePrivate : public HCircleGaugePrivate
{
public:
    int ringWidth = 10;
    QColor ringColor = QColor(200, 200, 200);
    QString unit;
    QString text;
};

HE_CONTROL_END_NAMESPACE
