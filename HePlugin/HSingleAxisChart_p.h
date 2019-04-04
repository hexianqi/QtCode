#ifndef HSINGLEAXISCHART_P_H
#define HSINGLEAXISCHART_P_H

#include "HSingleAxisChart.h"

class HSingleAxisChartPrivate
{
public:
    QAbstractAxis *axisX = nullptr;
    QAbstractAxis *axisY = nullptr;
};

#endif // HSINGLEAXISCHART_P_H
