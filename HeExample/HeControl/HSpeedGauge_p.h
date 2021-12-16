#pragma once

#include "HSpeedGauge.h"
#include "HCircleGauge_p.h"

HE_BEGIN_NAMESPACE

class HSpeedGaugePrivate : public HCircleGaugePrivate
{
public:
    HSpeedGaugePrivate();

public:
    int ringWidth = 10;
    int ringStart = 25;
    int ringMid = 50;
    int ringEnd = 25;
    QColor ringColorStart = QColor(2, 242, 177);
    QColor ringColorMid = QColor(45, 196, 248);
    QColor ringColorEnd = QColor(254, 68, 138);
};

HE_END_NAMESPACE
