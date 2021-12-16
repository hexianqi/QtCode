#pragma once

#include "HCarGauge.h"
#include "HCircleGauge_p.h"

HE_BEGIN_NAMESPACE

class HCarGaugePrivate : public HCircleGaugePrivate
{
public:
    HCarGaugePrivate();

public:
    QColor outerCircleColor = QColor(80, 80, 80);
    QColor innerCircleColor = QColor(60, 60, 60);
    QColor coverCircleColor = QColor(100, 100, 100);
    QColor centerCircleColor = QColor(250, 250, 250);
    QColor pieColorStart = QColor(24, 189, 155);
    QColor pieColorMid = QColor(218, 218, 0);
    QColor pieColorEnd = QColor(255, 107, 107);
    bool showOverlay = true;
    QColor overlayColor = QColor(255, 255, 255, 30);
    HCarGauge::PieStyle pieStyle = HCarGauge::PieStyle_Three;
    HControlType::PointerStyle pointerStyle = HControlType::PointerStyle_Indicator;
};

HE_END_NAMESPACE
