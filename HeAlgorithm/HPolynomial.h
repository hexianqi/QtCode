/***************************************************************************************************
**      2018-06-20  HPolynomial GSL多项式函数类。
**                  P(x) = a[0] + a[1] x + a[2] x^2 + ... + a[len-1] x^(len-1)
**                  http://www.gnu.org/software/gsl/doc/html/poly.html
***************************************************************************************************/

#ifndef HPOLYNOMIAL_H
#define HPOLYNOMIAL_H

#include "HAlgorithmGlobal.h"
#include <QPointF>

HE_ALGORITHM_BEGIN_NAMESPACE

class HE_ALGORITHM_EXPORT HPolynomial
{
public:
    // 求值
    static double eval(QVector<double> a, double x);
    // 求[0,n]阶导数值
    static QVector<double> evalDerivs(QVector<double> a, double x, int n);
    // 求根
    static QVector<QPointF> solveComplex(QVector<double> a);
    // 求根（ax^2 + bx + c = 0）
    static QVector<double> solveQuadratic(double a, double b, double c);
    // 求根（az^2 + bz + c = 0）
    static QVector<QPointF> solveQuadratiComplex(double a, double b, double c);
    // 求根（x^3 + ax^2 + bx + c = 0）
    static QVector<double> solveCubic(double a, double b, double c);
    // 求根（z^3 + az^2 + bz + c = 0）
    static QVector<QPointF> solveCubicComplex(double a, double b, double c);
};

HE_ALGORITHM_END_NAMESPACE

#endif // HPOLYNOMIAL_H
