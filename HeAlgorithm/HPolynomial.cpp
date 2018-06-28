#include "HPolynomial.h"
#include "gsl/gsl_poly.h"
#include <QVector>

HE_ALGORITHM_BEGIN_NAMESPACE

double HPolynomial::eval(QVector<double> a, double x)
{
    return gsl_poly_eval(a.data(), a.size(), x);
}

QVector<double> HPolynomial::evalDerivs(QVector<double> a, double x, int n)
{
    QVector<double> r(n);
    gsl_poly_eval_derivs(a.data(), a.size(), x, r.data(), r.size());
    return r;
}

QVector<QPointF> HPolynomial::solveComplex(QVector<double> a)
{
    QVector<QPointF> r;
    auto size = a.size();
    double z[size * 2 - 2];
    auto w = gsl_poly_complex_workspace_alloc(size);
    if (gsl_poly_complex_solve(a.data(), size, w, z) == 0)
    {
        for (int i = 0; i < size - 1; i++)
            r << QPointF(z[2*i], z[2*i+1]);
    }
    gsl_poly_complex_workspace_free (w);
    return r;
}

QVector<double> HPolynomial::solveQuadratic(double a, double b, double c)
{
    QVector<double> r;
    double x0,x1;
    int n = gsl_poly_solve_quadratic(a, b, c, &x0, &x1);
    if (n == 2)
        r << x0 << x1;
    if (n == 1)
        r << x0;
    return r;
}

QVector<QPointF> HPolynomial::solveQuadratiComplex(double a, double b, double c)
{
    QVector<QPointF> r;
    gsl_complex z0,z1;
    int n = gsl_poly_complex_solve_quadratic (a, b, c, &z0, &z1);
    if (n == 2)
        r << QPointF(GSL_REAL(z0), GSL_IMAG(z0)) << QPointF(GSL_REAL(z1), GSL_IMAG(z1));
    if (n == 1)
        r << QPointF(GSL_REAL(z0), GSL_IMAG(z0));
    return r;
}

QVector<double> HPolynomial::solveCubic(double a, double b, double c)
{
    QVector<double> r;
    double x0,x1,x2;
    int n = gsl_poly_solve_cubic (a, b, c, &x0, &x1, &x2);
    if (n == 3)
        r << x0 << x1 << x2;
    if (n == 1)
        r << x0;
    return r;
}

QVector<QPointF> HPolynomial::solveCubicComplex(double a, double b, double c)
{
    gsl_complex z0,z1,z2;
    gsl_poly_complex_solve_cubic(a, b, c, &z0, &z1, &z2);
    return QVector<QPointF>() << QPointF(GSL_REAL(z0), GSL_IMAG(z0)) << QPointF(GSL_REAL(z1), GSL_IMAG(z1)) << QPointF(GSL_REAL(z2), GSL_IMAG(z2));
}

HE_ALGORITHM_END_NAMESPACE
