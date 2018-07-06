#ifndef HABSTRACTCHARTEXTEND_P_H
#define HABSTRACTCHARTEXTEND_P_H

#include "HAbstractChartExtend.h"

class HAbstractChartExtendPrivate
{
public:
    HAbstractChartExtendPrivate(QChart *c);

public:
    QChart *chart;
};

#endif // HABSTRACTCHARTEXTEND_P_H
