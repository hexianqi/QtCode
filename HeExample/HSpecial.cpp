#include "HSpecial.h"
#include "gsl/gsl_sf.h"

HE_EXAMPLE_BEGIN_NAMESPACE

HSpecial::HSpecial()
{

}

double HSpecial::airyAi(double x)
{
    return gsl_sf_airy_Ai(x, GSL_PREC_DOUBLE);
}

double HSpecial::airyBi(double x)
{
    return gsl_sf_airy_Bi(x, GSL_PREC_DOUBLE);
}

HE_EXAMPLE_END_NAMESPACE
