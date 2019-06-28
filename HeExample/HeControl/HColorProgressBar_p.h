#ifndef HCOLORPROGRESSBAR_P_H
#define HCOLORPROGRESSBAR_P_H

#include "HColorProgressBar.h"
#include "HAbstractProgress_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HColorProgressBarPrivate : public HAbstractProgressPrivate
{
public:
    QColor barBackground = Qt::white;
    QColor barSplitLineColor = Qt::white;
    QColor barColor = QColor(255, 107, 107);
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
