#include "HBesselCylindrical.h"
#include "gsl/gsl_sf_bessel.h"

HE_BEGIN_NAMESPACE

double HBesselCylindrical::J0(double x)
{
    return gsl_sf_bessel_J0(x);
}

double HBesselCylindrical::J1(double x)
{
    return gsl_sf_bessel_J1(x);
}

double HBesselCylindrical::Jn(int n, double x)
{
    return gsl_sf_bessel_Jn(n, x);
}

QVector<double> HBesselCylindrical::Jn(int nmin, int nmax, double x)
{
    if (nmax < nmin)
        qSwap(nmin, nmax);

    QVector<double> r(nmax - nmin + 1);
    gsl_sf_bessel_Jn_array(nmin, nmax, x, r.data());
    return r;
}

double HBesselCylindrical::Y0(double x)
{
    return gsl_sf_bessel_Y0(x);
}

double HBesselCylindrical::Y1(double x)
{
    return gsl_sf_bessel_Y1(x);
}

double HBesselCylindrical::Yn(int n, double x)
{
    return gsl_sf_bessel_Yn(n, x);
}

QVector<double> HBesselCylindrical::Yn(int nmin, int nmax, double x)
{
    if (nmax < nmin)
        qSwap(nmin, nmax);

    QVector<double> r(nmax - nmin + 1);
    gsl_sf_bessel_Yn_array(nmin, nmax, x, r.data());
    return r;
}

double HBesselCylindrical::I0(double x)
{
    return gsl_sf_bessel_I0(x);
}

double HBesselCylindrical::I1(double x)
{
    return gsl_sf_bessel_I1(x);
}

double HBesselCylindrical::In(int n, double x)
{
    return gsl_sf_bessel_In(n, x);
}

QVector<double> HBesselCylindrical::In(int nmin, int nmax, double x)
{
    if (nmax < nmin)
        qSwap(nmin, nmax);

    QVector<double> r(nmax - nmin + 1);
    gsl_sf_bessel_In_array(nmin, nmax, x, r.data());
    return r;
}

double HBesselCylindrical::I0_scaled(double x)
{
    return gsl_sf_bessel_I0_scaled(x);
}

double HBesselCylindrical::I1_scaled(double x)
{
    return gsl_sf_bessel_I1_scaled(x);
}

double HBesselCylindrical::In_scaled(int n, double x)
{
    return gsl_sf_bessel_In_scaled(n, x);
}

QVector<double> HBesselCylindrical::In_scaled(int nmin, int nmax, double x)
{
    if (nmax < nmin)
        qSwap(nmin, nmax);

    QVector<double> r(nmax - nmin + 1);
    gsl_sf_bessel_In_scaled_array(nmin, nmax, x, r.data());
    return r;
}

double HBesselCylindrical::K0(double x)
{
    return gsl_sf_bessel_K0(x);
}

double HBesselCylindrical::K1(double x)
{
    return gsl_sf_bessel_K1(x);
}

double HBesselCylindrical::Kn(int n, double x)
{
    return gsl_sf_bessel_Kn(n, x);
}

QVector<double> HBesselCylindrical::Kn(int nmin, int nmax, double x)
{
    if (nmax < nmin)
        qSwap(nmin, nmax);

    QVector<double> r(nmax - nmin + 1);
    gsl_sf_bessel_Kn_array(nmin, nmax, x, r.data());
    return r;
}

double HBesselCylindrical::K0_scaled(double x)
{
    return gsl_sf_bessel_K0_scaled(x);
}

double HBesselCylindrical::K1_scaled(double x)
{
    return gsl_sf_bessel_K1_scaled(x);
}

double HBesselCylindrical::Kn_scaled(int n, double x)
{
    return gsl_sf_bessel_Kn_scaled(n, x);
}

QVector<double> HBesselCylindrical::Kn_scaled(int nmin, int nmax, double x)
{
    if (nmax < nmin)
        qSwap(nmin, nmax);

    QVector<double> r(nmax - nmin + 1);
    gsl_sf_bessel_Kn_scaled_array(nmin, nmax, x, r.data());
    return r;
}

HE_END_NAMESPACE
