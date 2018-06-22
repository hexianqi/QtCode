/***************************************************************************************************
**      2018-06-20  HPolynomials 多项式范例。
***************************************************************************************************/

#ifndef HPOLYNOMIALS_H
#define HPOLYNOMIALS_H

#include "HExampleGlobal.h"
#include <QPointF>

HE_EXAMPLE_BEGIN_NAMESPACE

class HE_EXAMPLE_EXPORT HPolynomials
{
public:
    // 求值
    double eval(QVector<double> a, double x);
    // 求根
    QVector<QPointF> solve(QVector<double> a);
};

HE_EXAMPLE_END_NAMESPACE

#endif // HPOLYNOMIALS_H
