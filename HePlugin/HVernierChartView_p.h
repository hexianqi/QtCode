#pragma once

#include "HVernierChartView.h"
#include "HZoomChartView_p.h"

class QGraphicsSimpleTextItem;

class HVernierChartViewPrivate : public HZoomChartViewPrivate
{
public:
    HGraphicsVernierTracking *tracking;
    QGraphicsSimpleTextItem *textLeft;
    QGraphicsSimpleTextItem *textCenter;
    QGraphicsSimpleTextItem *textRight;
    int decimals = 2;
};
