#pragma once

#include "HChromatismChartView.h"
#include "HZoomChartView_p.h"

class QGraphicsSimpleTextItem;

class HChromatismChartViewPrivate : public HZoomChartViewPrivate
{
public:
    HChromatismChart *chart;
    QGraphicsSimpleTextItem *pointFocusItem;

public:
    QPointF pointCenter;
    double sdcmStd = 0.0;
    double theta = 0.0;
    double axisA = 0.0;
    double axisB = 0.0;
    QPointF pointFocus;
    double sdcmFocus = 0.0;
};
