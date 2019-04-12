#ifndef HSINGLEAXISCHART_P_H
#define HSINGLEAXISCHART_P_H

#include "HSingleAxisChart.h"
#include "HChart_p.h"

class HSingleAxisChartPrivate : public HChartPrivate
{
public:
    QAbstractAxis *axisX = nullptr;
    QAbstractAxis *axisY = nullptr;
};

#endif // HSINGLEAXISCHART_P_H
