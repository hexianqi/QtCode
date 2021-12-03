#pragma once

#include "HTm30BarChart.h"
#include "HSingleAxisChart_p.h"

class HTm30BarChartPrivate : public HSingleAxisChartPrivate
{
public:
    QBarSeries *series = nullptr;
    QList<QBarSet *> set;
    QList<QColor> color;
};



