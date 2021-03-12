#pragma once

#include "HCie1931ChartView.h"
#include "HZoomChartView_p.h"

class QGraphicsSimpleTextItem;
class HPositionTracking;

class HCie1931ChartViewPrivate : public HZoomChartViewPrivate
{
public:
    HCie1931Chart *chart;
    HPositionTracking *tracking;
    QGraphicsSimpleTextItem *positionItem;
    QGraphicsSimpleTextItem *pointFocusItem;
};
