#include "HInterp.h"
#include "gsl/gsl_spline.h"
#include <functional>

using namespace std;

HE_ALGORITHM_BEGIN_NAMESPACE

const gsl_interp_type *trans(HInterp::HInterpType type)
{
    switch (type)
    {
    case HInterp::Linera:
        return gsl_interp_linear;
    case HInterp::Polynomial:
        return gsl_interp_polynomial;
    case HInterp::Cspline:
        return gsl_interp_cspline;
    case HInterp::CsplinePeriodic:
        return gsl_interp_cspline_periodic;
    case HInterp::Akima:
        return gsl_interp_akima;
    case HInterp::AkimaPeriodic:
        return gsl_interp_akima_periodic;
    default:
        return nullptr;
    }
    return nullptr;
}

void gslInterp(QPolygonF basis, HInterp::HInterpType type, std::function<void(gsl_spline *, gsl_interp_accel *)> func)
{
    auto t = trans(type);
    uint size = basis.size();
    Q_ASSERT(t != nullptr && size >= t->min_size);

    QVector<double> xa,ya;
    for (auto point : basis)
    {
        xa << point.x();
        ya << point.y();
    }

    auto acc = gsl_interp_accel_alloc();
    auto spline = gsl_spline_alloc(t, size);
    gsl_spline_init(spline, xa.data(), ya.data(), size);
    func(spline, acc);
    gsl_spline_free(spline);
    gsl_interp_accel_free(acc);
    return r;
}

double HInterp::eval(QPolygonF basis, double x, HInterpType type)
{
    return eval(basis, QVector<double>() << x, type).at(0);
}

QVector<double> HInterp::eval(QPolygonF basis, QVector<double> x, HInterpType type)
{
    auto t = trans(type);
    uint size = basis.size();
    Q_ASSERT(t != nullptr && size >= t->min_size);

    QVector<double> xa,ya,r;
    for (auto point : basis)
    {
        xa << point.x();
        ya << point.y();
    }

    auto acc = gsl_interp_accel_alloc();
    auto spline = gsl_spline_alloc(t, size);
    gsl_spline_init(spline, xa.data(), ya.data(), size);
    for (auto xi : x)
        r << gsl_spline_eval(spline, xi, acc);
    gsl_spline_free(spline);
    gsl_interp_accel_free(acc);
    return r;
}

QPolygonF HInterp::eval(QPolygonF basis, double a, double b, double interval, HInterpType type)
{
    QPolygonF r;
    QVector<double> x;
    if (b < a)
        qSwap(a, b);

    for (double t = a; t <= b; t += interval)
        x << t;

    auto y = eval(basis, x, type);
    for (int i = 0; i < x.size() && i < y.size(); i++)
        r << QPointF(x[i], y[i]);
    return r;
}

QVector<double> HInterp::evalDeriv(QPolygonF basis, QVector<double> x, HInterpType type)
{
    auto t = trans(type);
    uint size = basis.size();
    Q_ASSERT(t != nullptr && size >= t->min_size);

    QVector<double> xa,ya,r;
    for (auto point : basis)
    {
        xa << point.x();
        ya << point.y();
    }

    auto acc = gsl_interp_accel_alloc();
    auto spline = gsl_spline_alloc(t, size);
    gsl_spline_init(spline, xa.data(), ya.data(), size);
    for (auto xi : x)
        r << gsl_spline_eval_deriv(spline, xi, acc);
    gsl_spline_free(spline);
    gsl_interp_accel_free(acc);
    return r;
}

QVector<double> HInterp::evalDeriv2(QPolygonF basis, QVector<double> x, HInterp::HInterpType type)
{
    auto t = trans(type);
    uint size = basis.size();
    Q_ASSERT(t != nullptr && size >= t->min_size);

    QVector<double> xa,ya,r;
    for (auto point : basis)
    {
        xa << point.x();
        ya << point.y();
    }

    auto acc = gsl_interp_accel_alloc();
    auto spline = gsl_spline_alloc(t, size);
    gsl_spline_init(spline, xa.data(), ya.data(), size);
    for (auto xi : x)
        r << gsl_spline_eval_deriv2(spline, xi, acc);
    gsl_spline_free(spline);
    gsl_interp_accel_free(acc);
    return r;

}

double HInterp::evalInteg(QPolygonF basis, double a, double b, HInterpType type)
{
    auto t = trans(type);
    uint size = basis.size();
    Q_ASSERT(t != nullptr && size >= t->min_size);

    QVector<double> xa,ya;
    for (auto point : basis)
    {
        xa << point.x();
        ya << point.y();
    }

    auto acc = gsl_interp_accel_alloc();
    auto spline = gsl_spline_alloc(t, size);
    gsl_spline_init(spline, xa.data(), ya.data(), size);
    auto r = gsl_spline_eval_integ(spline, a, b, acc);
    gsl_spline_free(spline);
    gsl_interp_accel_free(acc);
    return r;
}

HE_ALGORITHM_END_NAMESPACE

