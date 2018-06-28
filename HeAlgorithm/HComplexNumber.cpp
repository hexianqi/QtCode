#include "HComplexNumber.h"
#include "gsl/gsl_complex_math.h"

HE_ALGORITHM_BEGIN_NAMESPACE

gsl_complex HComplexNumber::fromPoint(double x, double y)
{
    return gsl_complex_rect(x, y);
}

gsl_complex HComplexNumber::fromPolar(double r, double theta)
{
    return gsl_complex_polar(r, theta);
}

HE_ALGORITHM_END_NAMESPACE
