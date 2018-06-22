/***************************************************************************************************
**      2018-06-20  HInterpolation 插值范例。
***************************************************************************************************/

#ifndef HINTERPOLATION_H
#define HINTERPOLATION_H

#include "HExampleGlobal.h"
#include <QPolygonF>

HE_EXAMPLE_BEGIN_NAMESPACE

class HE_EXAMPLE_EXPORT HInterpolation
{
public:
    HInterpolation();

public:
    double splineEval(QPolygonF basis, double x);
    QVector<double> splineEval(QPolygonF basis, QVector<double> x);
    QPolygonF splineEval(QPolygonF basis, double x1, double x2, double interval = 0.1);


};

HE_EXAMPLE_END_NAMESPACE

#endif // HINTERPOLATION_H
