/***************************************************************************************************
**      2018-06-20  HLinearFit GSL线性最小二乘拟合函数类。
**                  http://www.gnu.org/software/gsl/doc/html/lls.html
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtGui/QPolygonF>

HE_BEGIN_NAMESPACE

class HLinearFit
{
public:
    // Y = c0 + c1 * x
    static QVector<double> linear(QPolygonF basis);
    static QVector<double> linear(QPolygonF basis, QVector<double> wa);
    static void linear(QPolygonF basis, QVector<double> &ca, QVector<double> &cova, double *sumsq);
    static void linear(QPolygonF basis, QVector<double> wa, QVector<double> &ca, QVector<double> &cova, double *chisq);
    static void linear_est(double x, QVector<double> ca, QVector<double> cova, double *y, double *y_err);

public:
    // Y = c0 * x
    static double mul(QPolygonF basis);
    static double mul(QPolygonF basis, QVector<double> wa);
    static void mul(QPolygonF basis, double *c, double *cov, double *sumsq);
    static void mul(QPolygonF basis, QVector<double> wa, double *c, double *cov, double *chisq);
    static void mul_est(double x, double c, double cov, double *y, double *y_err);
};

HE_END_NAMESPACE
