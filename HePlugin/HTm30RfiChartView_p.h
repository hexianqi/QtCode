#pragma once

#include "HTm30RfiChartView.h"
#include "HZoomChartView_p.h"

class HTm30RfiChartViewPrivate : public HZoomChartViewPrivate
{
public:
    HTm30BarChart *chart = nullptr;
    QList<QColor> color;
};



