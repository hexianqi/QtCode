#include "HInterpolation.h"
#include "gsl/gsl_spline.h"
#include <QVector>
#include <QPolygonF>

HE_EXAMPLE_BEGIN_NAMESPACE

HInterpolation::HInterpolation()
{

}

double HInterpolation::splineEval(QPolygonF basis, double x)
{
    QVector<double> xa,ya;
    for (auto p : basis)
    {
        xa << p.x();
        ya << p.y();
    }

    auto acc = gsl_interp_accel_alloc();
    auto spline = gsl_spline_alloc(gsl_interp_cspline, basis.size());
    gsl_spline_init(spline, xa.data(), ya.data(), basis.size());
    auto y = gsl_spline_eval(spline, x, acc);
    gsl_spline_free(spline);
    gsl_interp_accel_free(acc);
    return y;
}

QVector<double> HInterpolation::splineEval(QPolygonF basis, QVector<double> x)
{
    if (basis.size() < gsl_interp_cspline->min_size)
        return QVector<double>();

    QVector<double> xa,ya,r;
    for (auto p : basis)
    {
        xa << p.x();
        ya << p.y();
    }

    auto acc = gsl_interp_accel_alloc();
    auto spline = gsl_spline_alloc(gsl_interp_cspline, basis.size());
    gsl_spline_init(spline, xa.data(), ya.data(), basis.size());
    for (auto xi : x)
        r << gsl_spline_eval(spline, xi, acc);
    gsl_spline_free(spline);
    gsl_interp_accel_free(acc);
    return r;
}

QPolygonF HInterpolation::splineEval(QPolygonF basis, double x1, double x2, double interval)
{
    QPolygonF r;
    QVector<double> x;
    if (x2 < x1)
        qSwap(x1, x2);

    for (double t = x1; t < x2; t += interval)
        x << t;

    auto y = splineEval(basis, x);
    for (int i = 0; i < x.size() && i < y.size(); i++)
        r << QPointF(x[i], y[i]);
    return r;
}

HE_EXAMPLE_END_NAMESPACE
