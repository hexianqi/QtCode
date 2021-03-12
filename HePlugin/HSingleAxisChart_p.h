#pragma once

#include "HSingleAxisChart.h"
#include "HChart_p.h"

class HSingleAxisChartPrivate : public HChartPrivate
{
public:
    QAbstractAxis *axisX = nullptr;
    QAbstractAxis *axisY = nullptr;
};
