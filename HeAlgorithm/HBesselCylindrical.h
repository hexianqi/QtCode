/***************************************************************************************************
**      2018-12-06  HBesselCylindrical 圆柱贝塞尔函数类。
**                  http://www.gnu.org/software/gsl/doc/html/specfunc.html
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

class HBesselCylindrical
{
public: // 规则
    static double J0(double x);
    static double J1(double x);
    static double Jn(int n, double x);
    static QVector<double> Jn(int nmin, int nmax, double x);

public: // 不规则
    static double Y0(double x);
    static double Y1(double x);
    static double Yn(int n, double x);
    static QVector<double> Yn(int nmin, int nmax, double x);

public: // 规则修正
    static double I0(double x);
    static double I1(double x);
    static double In(int n, double x);
    static QVector<double> In(int nmin, int nmax, double x);
    static double I0_scaled(double x);
    static double I1_scaled(double x);
    static double In_scaled(int n, double x);
    static QVector<double> In_scaled(int nmin, int nmax, double x);

public: // 不规则修正
    static double K0(double x);
    static double K1(double x);
    static double Kn(int n, double x);
    static QVector<double> Kn(int nmin, int nmax, double x);
    static double K0_scaled(double x);
    static double K1_scaled(double x);
    static double Kn_scaled(int n, double x);
    static QVector<double> Kn_scaled(int nmin, int nmax, double x);
};

HE_END_NAMESPACE
