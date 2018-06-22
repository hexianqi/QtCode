#include "HComplexNumbers.h"
#include "gsl/gsl_complex_math.h"

HE_EXAMPLE_BEGIN_NAMESPACE

gsl_complex HComplexNumbers::fromPoint(double x, double y)
{
    return gsl_complex_rect(x, y);
}

gsl_complex HComplexNumbers::fromPolar(double r, double theta)
{
    return gsl_complex_polar(r, theta);
}

gsl_complex HComplexNumbers::add(gsl_complex a, gsl_complex b)
{
    return gsl_complex_add(a, b);

}

HE_EXAMPLE_END_NAMESPACE
