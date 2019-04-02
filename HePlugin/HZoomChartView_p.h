#ifndef HZOOMCHARTVIEW_P_H
#define HZOOMCHARTVIEW_P_H

#include "HZoomChartView.h"
#include "HChartView_p.h"

class HZoomChartViewPrivate : public HChartViewPrivate
{
public:
    QAction *actionZoomIn;
    QAction *actionZoomOut;
    QAction *actionZoomReset;
};

#endif // HZOOMCHARTVIEW_P_H
