#include "HBesselSpherical.h"
#include "gsl/gsl_sf_bessel.h"
#include <QVector>

HE_ALGORITHM_BEGIN_NAMESPACE

double HBesselSpherical::j0(double x)
{
    return gsl_sf_bessel_j0(x);
}

double HBesselSpherical::j1(double x)
{
    return gsl_sf_bessel_j1(x);
}

double HBesselSpherical::j2(double x)
{
    return gsl_sf_bessel_j2(x);
}

double HBesselSpherical::jl(int l, double x)
{
    return gsl_sf_bessel_jl(l, x);
}

QVector<double> HBesselSpherical::jls(int lmax, double x)
{
    QVector<double> r(lmax + 1);
    gsl_sf_bessel_jl_array(lmax, x, r.data());
    return r;
}

QVector<double> HBesselSpherical::jl_steed(int lmax, double x)
{
    QVector<double> r(lmax + 1);
    gsl_sf_bessel_jl_steed_array(lmax, x, r.data());
    return r;
}

double HBesselSpherical::y0(double x)
{
    return gsl_sf_bessel_y0(x);
}

double HBesselSpherical::y1(double x)
{
    return gsl_sf_bessel_y1(x);
}

double HBesselSpherical::y2(double x)
{
    return gsl_sf_bessel_y2(x);
}

double HBesselSpherical::yl(int l, double x)
{
    return gsl_sf_bessel_yl(l, x);
}

QVector<double> HBesselSpherical::yls(int lmax, double x)
{
    QVector<double> r(lmax + 1);
    gsl_sf_bessel_yl_array(lmax, x, r.data());
    return r;
}

double HBesselSpherical::i0_scaled(double x)
{
    return gsl_sf_bessel_i0_scaled(x);
}

double HBesselSpherical::i1_scaled(double x)
{
    return gsl_sf_bessel_i1_scaled(x);
}

double HBesselSpherical::i2_scaled(double x)
{
    return gsl_sf_bessel_i2_scaled(x);
}

double HBesselSpherical::il_scaled(int l, double x)
{
    return gsl_sf_bessel_il_scaled(l, x);
}

QVector<double> HBesselSpherical::il_scaleds(int lmax, double x)
{
    QVector<double> r(lmax + 1);
    gsl_sf_bessel_il_scaled_array(lmax, x, r.data());
    return r;
}

double HBesselSpherical::k0_scaled(double x)
{
    return gsl_sf_bessel_k0_scaled(x);
}

double HBesselSpherical::k1_scaled(double x)
{
    return gsl_sf_bessel_k1_scaled(x);
}

double HBesselSpherical::k2_scaled(double x)
{
    return gsl_sf_bessel_k2_scaled(x);
}

double HBesselSpherical::kl_scaled(int l, double x)
{
    return gsl_sf_bessel_kl_scaled(l, x);
}

QVector<double> HBesselSpherical::kl_scaleds(int lmax, double x)
{
    QVector<double> r(lmax + 1);
    gsl_sf_bessel_kl_scaled_array(lmax, x, r.data());
    return r;
}

HE_ALGORITHM_END_NAMESPACE
