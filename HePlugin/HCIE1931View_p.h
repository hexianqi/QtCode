#ifndef HCIE1931VIEW_P_H
#define HCIE1931VIEW_P_H

#include "HCIE1931View.h"
#include "HZoomChartView_p.h"

class QGraphicsSimpleTextItem;
class HCIE1931Chart;

class HCIE1931ViewPrivate : public HZoomChartViewPrivate
{
    Q_DECLARE_PUBLIC(HCIE1931View)

public:
    HCIE1931ViewPrivate(HCIE1931View *q);

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

#endif // HCIE1931VIEW_P_H
