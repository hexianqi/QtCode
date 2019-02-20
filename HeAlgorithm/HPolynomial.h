/***************************************************************************************************
**      2018-06-20  HPolynomial GSL多项式函数类。
**                  P(x) = c[0] + c[1] x + c[2] x^2 + ... + c[len-1] x^(len-1)
**                  http://www.gnu.org/software/gsl/doc/html/poly.html
***************************************************************************************************/

#ifndef HPOLYNOMIAL_H
#define HPOLYNOMIAL_H

#include "HAlgorithmGlobal.h"
#include "gsl/gsl_complex.h"

HE_ALGORITHM_BEGIN_NAMESPACE

class HE_ALGORITHM_EXPORT HPolynomial
{
public:
    // 求值
    static double eval(QVector<double> c, double x);
    static gsl_complex complex_eval(QVector<double> c, gsl_complex z);
    static gsl_complex complex_eval(QVector<gsl_complex> c, gsl_complex z);
    // 求[0,n]阶导数值
    static QVector<double> eval_derivs(QVector<double> c, double x, int n);
    // 求根
    static QVector<gsl_complex> complex_solve(QVector<double> a);
    // 求根 ax^2 + bx + c = 0
    static QVector<double> solve_quadratic(double a, double b, double c);
    // 求根 az^2 + bz + c = 0
    static QVector<gsl_complex> complex_solve_quadratic(double a, double b, double c);
    // 求根 x^3 + ax^2 + bx + c = 0
    static QVector<double> solve_cubic(double a, double b, double c);
    // 求根 z^3 + az^2 + bz + c = 0
    static QVector<gsl_complex> complex_solve_cubic(double a, double b, double c);
};

HE_ALGORITHM_END_NAMESPACE

#endif // HPOLYNOMIAL_H
