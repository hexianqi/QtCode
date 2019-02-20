/***************************************************************************************************
**      2018-12-06  HBesselCylindrical 圆柱贝塞尔函数类。
**                  http://www.gnu.org/software/gsl/doc/html/specfunc.html
***************************************************************************************************/

#ifndef HBESSELCYLINDRIAL_H
#define HBESSELCYLINDRIAL_H

#include "HAlgorithmGlobal.h"

HE_ALGORITHM_BEGIN_NAMESPACE

class HE_ALGORITHM_EXPORT HBesselCylindrical
{
public: // 规则
    double J0(double x);
    double J1(double x);
    double Jn(int n, double x);
    QVector<double> Jn(int nmin, int nmax, double x);

public: // 不规则
    double Y0(double x);
    double Y1(double x);
    double Yn(int n, double x);
    QVector<double> Yn(int nmin, int nmax, double x);

public: // 规则修正
    double I0(double x);
    double I1(double x);
    double In(int n, double x);
    QVector<double> In(int nmin, int nmax, double x);
    double I0_scaled(double x);
    double I1_scaled(double x);
    double In_scaled(int n, double x);
    QVector<double> In_scaled(int nmin, int nmax, double x);

public: // 不规则修正
    double K0(double x);
    double K1(double x);
    double Kn(int n, double x);
    QVector<double> Kn(int nmin, int nmax, double x);
    double K0_scaled(double x);
    double K1_scaled(double x);
    double Kn_scaled(int n, double x);
    QVector<double> Kn_scaled(int nmin, int nmax, double x);
};

HE_ALGORITHM_END_NAMESPACE

#endif // HBESSELCYLINDRIAL_H
