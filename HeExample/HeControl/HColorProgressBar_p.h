#pragma once

#include "HColorProgressBar.h"
#include "HAbstractProgress_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HColorProgressBarPrivate : public HAbstractProgressPrivate
{
public:
    int radius = 10;
    HColorProgressBar::TextPosition textPosition = HColorProgressBar::TextPosition_OutBar;
    QColor textForeColor = Qt::black;
    QColor textBackColor = Qt::white;
    HColorProgressBar::BarStyle barStyle = HColorProgressBar::BarStyle_Solid;
    QColor barForeColor = QColor(255, 107, 107);
    QColor barForeAlternateColor = QColor(255, 107, 10);
    QColor barBackColor = Qt::white;
    QGradientStops gradientData;
    int barStepSpace = 5;
    int barStepDelta = 0;
    int barStepSize = 2;
};

HE_CONTROL_END_NAMESPACE
