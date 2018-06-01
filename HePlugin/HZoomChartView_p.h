#ifndef HZOOMCHARTVIEW_P_H
#define HZOOMCHARTVIEW_P_H

#include "HZoomChartView.h"

class HPositionTracking;

class HZoomChartViewPrivate
{
public:
    HZoomChartViewPrivate(HZoomChartView *q);

public:
    HZoomChartView *q_ptr;
    QAction *actionZoomIn;
    QAction *actionZoomOut;
    QAction *actionZoomReset;
};

#endif // HZOOMCHARTVIEW_P_H
