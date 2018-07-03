/***************************************************************************************************
**      2018-06-20  HMultiFit GSL最小二乘拟合函数类。
**                  http://www.gnu.org/software/gsl/doc/html/lls.html
***************************************************************************************************/

#ifndef HMULTIFIT_H
#define HMULTIFIT_H

#include "HAlgorithmGlobal.h"
#include <QPolygonF>

HE_ALGORITHM_BEGIN_NAMESPACE

enum HRobustType
{
    Default,    //  = Bisquare
    Bisquare,   // t = 4.685; w(e) = (1 − e^2)^2, |e| <= 1; w(e) = 0, |e| > 1
    Cauchy,     // t = 2.385; w(e) = 1 / (1 + e^2)
    Fair,       // t = 1.400; w(e) = 1 / (1 + |e|)
    Huber,      // t = 1.345; w(e) = 1, |e| <= 1; w(e) = 1 / |e|, |e| > 1
    Ols,        // t = 1;     w(e) = 1
    Welsch      // t = 2.985; w(e) = exp(−e^2)
};

class HE_ALGORITHM_EXPORT HMultiFit
{
public:
    HMultiFit();

public:
    // P(x) = a[0] + a[1] x + a[2] x^2 + ... + a[len-1] x^(len-1)
    static void linear(QPolygonF basis, QVector<double> &c, QVector<double> &cov, double *chisq);
    static void linear(QPolygonF basis, QVector<double> w, QVector<double> &c, QVector<double> &cov, double *chisq);
    static void linearEst(double x, QVector<double> c, QVector<double> cov, double *y, double *y_err);
    static void robust(QPolygonF basis, QVector<double> &c, QVector<double> &cov, HRobustType type = HRobustType::Default);
    static void robustEst(double x, QVector<double> c, QVector<double> cov, double *y, double *y_err);
};

HE_ALGORITHM_END_NAMESPACE

#endif // HMULTIFIT_H
