#pragma once

#include "HTm30SpdChartView.h"
#include "HZoomChartView_p.h"
#include <QtCharts/QLineSeries>

class HTm30SpdChartViewPrivate : public HZoomChartViewPrivate
{
public:
    QLineSeries *testSeries;
    QLineSeries *references;
};



