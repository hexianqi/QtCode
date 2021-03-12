/***************************************************************************************************
**      2018-06-28  HComplexNumber GSL复数函数类。
**                  http://www.gnu.org/software/gsl/doc/html/complex.html
***************************************************************************************************/

#pragma once

#include "HAlgorithmGlobal.h"
#include "gsl/gsl_complex.h"
#include <QtCore/QPointF>

HE_ALGORITHM_BEGIN_NAMESPACE

class HComplexNumber
{
public:
    // z = x + y * i
    static gsl_complex fromPoint(double x, double y);
    // z = r * exp^(i * θ) = r(cos(θ) + sin(θ) * i)
    static gsl_complex fromPolar(double r, double theta);
};

HE_ALGORITHM_END_NAMESPACE
