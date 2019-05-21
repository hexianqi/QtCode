#ifndef HCHROMATISMCHARTVIEW_P_H
#define HCHROMATISMCHARTVIEW_P_H

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
    double stdSdcm = 0.0;
    double stdTheta = 0.0;
    double stdA = 0.0;
    double stdB = 0.0;
    QPointF pointFocus;
    double sdcm = 0.0;
};

#endif // HCHROMATISMCHARTVIEW_P_H
