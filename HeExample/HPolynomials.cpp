#include "HPolynomials.h"
#include "gsl/gsl_poly.h"
#include <QVector>

HE_EXAMPLE_BEGIN_NAMESPACE

double HPolynomials::eval(QVector<double> a, double x)
{
    return gsl_poly_eval(a.data(), a.size(), x);
}

QVector<QPointF> HPolynomials::solve(QVector<double> a)
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

HE_EXAMPLE_END_NAMESPACE
