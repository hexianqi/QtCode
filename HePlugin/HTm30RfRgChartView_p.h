#pragma once

#include "HTm30RfRgChartView.h"
#include "HZoomChartView_p.h"
#include <QtCharts/QScatterSeries>

class HTm30RfRgChartViewPrivate : public HZoomChartViewPrivate
{
public:
    QScatterSeries *point = nullptr;
};



