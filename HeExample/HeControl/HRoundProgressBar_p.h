#pragma once

#include "HRoundProgressBar.h"
#include "HAbstractProgress_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HRoundProgressBarPrivate : public HAbstractProgressPrivate
{
public:
    HRoundProgressBar::BarStyle barStyle = HRoundProgressBar::BarStyle_Donut;
    bool reverse = false;
    int angleStart = 0;
    bool drawExcircle = true;
    bool drawDataCircle = true;
    bool drawInnerCircle = true;
    bool drawText = true;
    QString format = QString("%p%");
    double excircleWidth = 1;
    double dataCircleWidth = 1;
    QGradientStops gradientData;

public:
    bool rebuildBrush = false;
    QRectF outerRect;
    QRectF innerRect;
    int outerRadius;
    double innerRadius;
};

HE_CONTROL_END_NAMESPACE
