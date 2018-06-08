#ifndef HSINGLEAXISCHART_P_H
#define HSINGLEAXISCHART_P_H

#include "HSingleAxisChart.h"

class HSingleAxisChartPrivate
{
public:
    HSingleAxisChartPrivate(HSingleAxisChart *q);

public:
    HSingleAxisChart *q_ptr;
    QAbstractAxis *axisX;
    QAbstractAxis *axisY;
};

#endif // HSINGLEAXISCHART_P_H
