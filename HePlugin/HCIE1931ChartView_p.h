#ifndef HCIE1931CHARTVIEW_P_H
#define HCIE1931CHARTVIEW_P_H

#include "HCIE1931ChartView.h"
#include "HZoomChartView_p.h"

class QGraphicsSimpleTextItem;
class HPositionTracking;

class HCIE1931ChartViewPrivate : public HZoomChartViewPrivate
{
public:
    HCIE1931Chart *chart;
    HPositionTracking *tracking;
    QGraphicsSimpleTextItem *positionItem;
    QGraphicsSimpleTextItem *pointFocusItem;
    QAction *actionEnableCIE;
    QAction *actionEnableHorseshoe;
    QAction *actionEnablePlanckian;
    QAction *actionEnableGrade;
    QAction *actionEnablePoint;
    QAction *actionClearPoint;
};

#endif // HCIE1931CHARTVIEW_P_H
