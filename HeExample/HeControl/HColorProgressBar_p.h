#ifndef HCOLORPROGRESSBAR_P_H
#define HCOLORPROGRESSBAR_P_H

#include "HColorProgressBar.h"

HE_CONTROL_BEGIN_NAMESPACE

class HColorProgressBarPrivate
{
public:
    double minimum = 0.0;
    double maximum = 100.0;
    double value = 24.0;
    QColor barBackground = Qt::white;
    QColor barSplitLineColor = Qt::white;
    QColor barColor = QColor(255, 107, 107);
    int decimal = 0;
    int space = 5;
    int barSplitLineStep = 0;
    bool showBarSplitLine = false;

    int radiusX = 5;
    int radiusY = 5;
    QRectF textRect;
    QRectF barRect;
};

HE_CONTROL_END_NAMESPACE

#endif // HCOLORPROGRESSBAR_P_H
