#include "HPolynomial.h"
#include "gsl/gsl_poly.h"
#include "gsl/gsl_complex_math.h"
#include <QtCore/QVector>

HE_ALGORITHM_BEGIN_NAMESPACE

double HPolynomial::eval(QVector<double> c, double x)
{
    return gsl_poly_eval(c.data(), c.size(), x);
}

gsl_complex HPolynomial::complex_eval(QVector<double> c, gsl_complex z)
{
    return gsl_poly_complex_eval(c.data(), c.size(), z);
}

gsl_complex HPolynomial::complex_eval(QVector<gsl_complex> c, gsl_complex z)
{
    return gsl_complex_poly_complex_eval(c.data(), c.size(), z);
}

QVector<double> HPolynomial::eval_derivs(QVector<double> c, double x, int n)
{
    QVector<double> r(n);
    gsl_poly_eval_derivs(c.data(), size_t(c.size()), x, r.data(), size_t(r.size()));
    return r;
}

QVector<gsl_complex> HPolynomial::complex_solve(QVector<double> a)
{
    QVector<gsl_complex> r;
    auto size = size_t(a.size());
    auto z = new double[size * 2 - 2];
    auto w = gsl_poly_complex_workspace_alloc(size);
    if (gsl_poly_complex_solve(a.data(), size, w, z) == 0)
    {
        for (size_t i = 0; i < size - 1; i++)
            r << gsl_complex_rect(z[2 * i], z[2 * i + 1]);
    }
    gsl_poly_complex_workspace_free(w);
    return r;
}

QVector<double> HPolynomial::solve_quadratic(double a, double b, double c)
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

QVector<gsl_complex> HPolynomial::complex_solve_quadratic(double a, double b, double c)
{
    QVector<gsl_complex> r;
    gsl_complex z0,z1;
    int n = gsl_poly_complex_solve_quadratic(a, b, c, &z0, &z1);
    if (n == 2)
        r << z0 << z1;
    if (n == 1)
        r << z0;
    return r;
}

QVector<double> HPolynomial::solve_cubic(double a, double b, double c)
{
    QVector<double> r;
    double x0,x1,x2;
    int n = gsl_poly_solve_cubic(a, b, c, &x0, &x1, &x2);
    if (n == 3)
        r << x0 << x1 << x2;
    if (n == 1)
        r << x0;
    return r;
}

QVector<gsl_complex> HPolynomial::complex_solve_cubic(double a, double b, double c)
{
    QVector<gsl_complex> r;
    gsl_complex z0,z1,z2;
    int n = gsl_poly_complex_solve_cubic(a, b, c, &z0, &z1, &z2);
    if (n == 3)
        r << z0 << z1 << z2;
    if (n == 1)
        r << z0;
    return r;
}

HE_ALGORITHM_END_NAMESPACE
