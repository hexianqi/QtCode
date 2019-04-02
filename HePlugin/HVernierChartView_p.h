#ifndef HVERNIERCHARTVIEW_P_H
#define HVERNIERCHARTVIEW_P_H

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


#endif // HVERNIERCHARTVIEW_P_H
