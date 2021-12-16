/***************************************************************************************************
**      2018-12-06  HBesselSpherical 球形贝塞尔函数类。
**                  http://www.gnu.org/software/gsl/doc/html/specfunc.html
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QVector>

HE_BEGIN_NAMESPACE

class HBesselSpherical
{
public: // 规则
    static double j0(double x);
    static double j1(double x);
    static double j2(double x);
    static double jl(int l, double x);
    static QVector<double> jls(int lmax, double x);
    static QVector<double> jl_steed(int lmax, double x);

public: // 不规则
    static double y0(double x);
    static double y1(double x);
    static double y2(double x);
    static double yl(int l, double x);
    static QVector<double> yls(int lmax, double x);

public: // 规则修正
    static double i0_scaled(double x);
    static double i1_scaled(double x);
    static double i2_scaled(double x);
    static double il_scaled(int l, double x);
    static QVector<double> il_scaleds(int lmax, double x);

public: // 不规则修正
    static double k0_scaled(double x);
    static double k1_scaled(double x);
    static double k2_scaled(double x);
    static double kl_scaled(int l, double x);
    static QVector<double> kl_scaleds(int lmax, double x);
};

HE_END_NAMESPACE
