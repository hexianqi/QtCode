#ifndef HABSTRACTCHARTEXTEND_P_H
#define HABSTRACTCHARTEXTEND_P_H

#include "HAbstractChartExtend.h"

class HAbstractChartExtendPrivate
{
public:
    HAbstractChartExtendPrivate(QChart *p = nullptr);

public:
    QChart *chart = nullptr;
};

#endif // HABSTRACTCHARTEXTEND_P_H
