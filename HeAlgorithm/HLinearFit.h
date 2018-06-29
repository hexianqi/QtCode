/***************************************************************************************************
**      2018-06-20  HLinearFit GSL线性最小二乘拟合函数类。
**                  http://www.gnu.org/software/gsl/doc/html/lls.html
***************************************************************************************************/

#ifndef HLINEARFIT_H
#define HLINEARFIT_H

#include "HAlgorithmGlobal.h"
#include <QPolygonF>

HE_ALGORITHM_BEGIN_NAMESPACE

class HE_ALGORITHM_EXPORT HLinearFit
{
public:
    // Y = c0 + c1 * x
    static QVector<double> linear(QPolygonF basis);
    static QVector<double> linear(QPolygonF basis, QVector<double> w);
    static void linear(QPolygonF basis, QVector<double> &c, QVector<double> &cov, double *sumsq);
    static void linear(QPolygonF basis, QVector<double> w, QVector<double> &c, QVector<double> &cov, double *chisq);
    static void linearEst(double x, QVector<double> c, QVector<double> cov, double *y, double *y_err);

public:
    // Y = c0 * x
    static double mul(QPolygonF basis);
    static double mul(QPolygonF basis, QVector<double> w);
    static void mul(QPolygonF basis, double *c, double *cov, double *sumsq);
    static void mul(QPolygonF basis, QVector<double> w, double *c, double *cov, double *chisq);
    static void mulEst(double x, double c, double cov, double *y, double *y_err);
};

HE_ALGORITHM_END_NAMESPACE

#endif // HLINEARFIT_H
