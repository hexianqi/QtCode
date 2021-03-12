#pragma once

#include "HChromatismWidget.h"
#include "HCartesianWidget_p.h"

class HChromatismWidgetPrivate : public HCartesianWidgetPrivate
{
public:
    HChromatismWidgetPrivate();

public:
    QColor colorPointFocus = Qt::red;
    QColor colorTitle = Qt::black;
    QColor colorBody = Qt::red;
    QFont fontTitle;
    QFont fontBody;

public:
    QString title;
    QPointF pointFocus;
    QPointF pointCenter;
    double sdcmStd = 0.0;
    double theta = 0.0;
    double axisA = 0.0;
    double axisB = 0.0;
    double sdcmFocus = 0.0;
};
