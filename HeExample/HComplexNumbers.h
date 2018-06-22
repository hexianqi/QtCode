/***************************************************************************************************
**      2018-06-20  HComplexNumbers 复数范例。
***************************************************************************************************/

#ifndef HCOMPLEXNUMBERS_H
#define HCOMPLEXNUMBERS_H

#include "HExampleGlobal.h"
#include "gsl/gsl_complex.h"

HE_EXAMPLE_BEGIN_NAMESPACE

class HE_EXAMPLE_EXPORT HComplexNumbers
{
public:
    gsl_complex fromPoint(double x, double y);
    gsl_complex fromPolar(double r, double theta);
    gsl_complex add(gsl_complex a, gsl_complex b);
};

HE_EXAMPLE_END_NAMESPACE

#endif // HCOMPLEXNUMBERS_H
