/***************************************************************************************************
**      2018-06-20  HMultiFit GSL最小二乘拟合函数类。
**                  http://www.gnu.org/software/gsl/doc/html/lls.html
***************************************************************************************************/

#ifndef HMULTIFIT_H
#define HMULTIFIT_H

#include "HAlgorithmGlobal.h"
#include <QtGui/QPolygonF>

HE_ALGORITHM_BEGIN_NAMESPACE

class HE_ALGORITHM_EXPORT HMultiFit
{
public:
    enum RobustType
    {
        Default,    //  = Bisquare
        Bisquare,   // t = 4.685; w(e) = (1 − e^2)^2, |e| <= 1; w(e) = 0, |e| > 1
        Cauchy,     // t = 2.385; w(e) = 1 / (1 + e^2)
        Fair,       // t = 1.400; w(e) = 1 / (1 + |e|)
        Huber,      // t = 1.345; w(e) = 1, |e| <= 1; w(e) = 1 / |e|, |e| > 1
        Ols,        // t = 1;     w(e) = 1
        Welsch      // t = 2.985; w(e) = exp(−e^2)
    };

public:
    // P(x) = c[0] + c[1] x + c[2] x^2 + ... + c[len-1] x^(len-1)
    static void linear(QPolygonF basis, QVector<double> &ca, QVector<double> &cova, double *chisq);
    static void linear(QPolygonF basis, QVector<double> wa, QVector<double> &ca, QVector<double> &cova, double *chisq);
    static void linear_est(double x, QVector<double> ca, QVector<double> cova, double *y, double *y_err);
    static void robust(QPolygonF basis, QVector<double> &ca, QVector<double> &cova, RobustType type = Default);
    static void robust_est(double x, QVector<double> ca, QVector<double> cova, double *y, double *y_err);
};

HE_ALGORITHM_END_NAMESPACE

#endif // HMULTIFIT_H
