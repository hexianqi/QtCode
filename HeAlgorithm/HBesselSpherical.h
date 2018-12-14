/***************************************************************************************************
**      2018-12-06  HBesselSpherical 球形贝塞尔函数类。
**                  http://www.gnu.org/software/gsl/doc/html/specfunc.html
***************************************************************************************************/

#ifndef HBESSELSPHERICAL_H
#define HBESSELSPHERICAL_H

#include "HAlgorithmGlobal.h"

HE_ALGORITHM_BEGIN_NAMESPACE

class HE_ALGORITHM_EXPORT HBesselSpherical
{
public: // 规则
    double j0(double x);
    double j1(double x);
    double j2(double x);
    double jl(int l, double x);
    QVector<double> jls(int lmax, double x);
    QVector<double> jl_steed(int lmax, double x);

public: // 不规则
    double y0(double x);
    double y1(double x);
    double y2(double x);
    double yl(int l, double x);
    QVector<double> yls(int lmax, double x);

public: // 规则修正
    double i0_scaled(double x);
    double i1_scaled(double x);
    double i2_scaled(double x);
    double il_scaled(int l, double x);
    QVector<double> il_scaleds(int lmax, double x);

public: // 不规则修正
    double k0_scaled(double x);
    double k1_scaled(double x);
    double k2_scaled(double x);
    double kl_scaled(int l, double x);
    QVector<double> kl_scaleds(int lmax, double x);
};

HE_ALGORITHM_END_NAMESPACE

#endif // HBESSELSPHERICAL_H
