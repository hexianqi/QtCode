#include "HSpecialFunction.h"
#include "gsl/gsl_sf.h"
#include <QVector>

HE_ALGORITHM_BEGIN_NAMESPACE

double HSpecialFunction::airyAi(double x)
{
    return gsl_sf_airy_Ai(x, GSL_PREC_DOUBLE);
}

double HSpecialFunction::airyBi(double x)
{
    return gsl_sf_airy_Bi(x, GSL_PREC_DOUBLE);
}

double HSpecialFunction::besselJ0(double x)
{
    return gsl_sf_bessel_J0(x);
}

double HSpecialFunction::besselJ1(double x)
{
    return gsl_sf_bessel_J1(x);
}

double HSpecialFunction::besselJn(int n, double x)
{
    return gsl_sf_bessel_Jn(n, x);
}

QVector<double> HSpecialFunction::besselJn(int nmin, int nmax, double x)
{
    if (nmax < nmin)
        qSwap(nmin, nmax);

    QVector<double> r(nmax - nmin + 1);
    gsl_sf_bessel_Jn_array(nmin, nmax, x, r.data());
    return r;
}

HE_ALGORITHM_END_NAMESPACE
