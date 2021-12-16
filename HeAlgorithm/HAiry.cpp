#include "HAiry.h"
#include "gsl/gsl_sf_airy.h"

HE_BEGIN_NAMESPACE

double HAiry::Ai(double x)
{
    return gsl_sf_airy_Ai(x, GSL_PREC_DOUBLE);
}

double HAiry::Bi(double x)
{
    return gsl_sf_airy_Bi(x, GSL_PREC_DOUBLE);
}

double HAiry::Ai_scaled(double x)
{
    return gsl_sf_airy_Ai_scaled(x, GSL_PREC_DOUBLE);
}

double HAiry::Bi_scaled(double x)
{
    return gsl_sf_airy_Bi_scaled(x, GSL_PREC_DOUBLE);
}

double HAiry::Ai_deriv(double x)
{
    return gsl_sf_airy_Ai_deriv(x, GSL_PREC_DOUBLE);
}

double HAiry::Bi_deriv(double x)
{
    return gsl_sf_airy_Bi_deriv(x, GSL_PREC_DOUBLE);
}

double HAiry::Ai_deriv_scaled(double x)
{
    return gsl_sf_airy_Ai_deriv_scaled(x, GSL_PREC_DOUBLE);
}

double HAiry::Bi_deriv_Scaled(double x)
{
    return gsl_sf_airy_Bi_deriv_scaled(x, GSL_PREC_DOUBLE);
}

double HAiry::zero_Ai(unsigned int s)
{
    return gsl_sf_airy_zero_Ai(s);
}

double HAiry::zero_Bi(unsigned int s)
{
    return gsl_sf_airy_zero_Ai(s);
}

double HAiry::zero_Ai_deriv(unsigned int s)
{
    return gsl_sf_airy_zero_Ai_deriv(s);
}

double HAiry::zero_Bi_deriv(unsigned int s)
{
    return gsl_sf_airy_zero_Bi_deriv(s);
}

HE_END_NAMESPACE
