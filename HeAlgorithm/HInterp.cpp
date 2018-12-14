#include "HInterp.h"
#include "HGslHelper.h"
#include "gsl/gsl_spline.h"
#include <functional>

HE_ALGORITHM_BEGIN_NAMESPACE

const gsl_interp_type *toGsl(HInterpType type)
{
    switch (type)
    {
    case Linera:
        return gsl_interp_linear;
    case Polynomial:
        return gsl_interp_polynomial;
    case Cspline:
        return gsl_interp_cspline;
    case CsplinePeriodic:
        return gsl_interp_cspline_periodic;
    case Akima:
        return gsl_interp_akima;
    case AkimaPeriodic:
        return gsl_interp_akima_periodic;
    case Steffen:
        return gsl_interp_steffen;
    default:
        return gsl_interp_linear;
    }
}

void doInterp(QPolygonF basis, HInterpType type, std::function<void(gsl_spline *, gsl_interp_accel *)> func)
{
    auto t = toGsl(type);
    size_t size = basis.size();
    Q_ASSERT(size >= t->min_size);

    QVector<double> x, y;
    HGslHelper::split(basis, x, y);
    auto acc = gsl_interp_accel_alloc();
    auto spline = gsl_spline_alloc(t, size);
    gsl_spline_init(spline, x.data(), y.data(), size);
    spline->interp->xmin = __DBL_MIN__;
    spline->interp->xmax = __DBL_MAX__;
    func(spline, acc);
    gsl_spline_free(spline);
    gsl_interp_accel_free(acc);
}

double HInterp::eval(QPolygonF basis, double x, HInterpType type)
{
    return eval(basis, QVector<double>() << x, type).at(0);
}

QVector<double> HInterp::eval(QPolygonF basis, QVector<double> xa, HInterpType type)
{
    QVector<double> r;
    auto func = [&](gsl_spline *spline, gsl_interp_accel *acc)
    {
        for (auto xi : xa)
            r << gsl_spline_eval(spline, xi, acc);
    };
    doInterp(basis, type, func);
    return r;
}

QPolygonF HInterp::eval(QPolygonF basis, double a, double b, double interval, HInterpType type)
{
    QVector<double> x;
    if (b < a)
        qSwap(a, b);
    for (double t = a; t <= b; t += interval)
        x << t;
    auto y = eval(basis, x, type);
    return HGslHelper::join(x, y);
}

QVector<double> HInterp::eval_deriv(QPolygonF basis, QVector<double> xa, HInterpType type)
{
    QVector<double> r;
    auto func = [&](gsl_spline *spline, gsl_interp_accel *acc)
    {
        for (auto xi : xa)
            r << gsl_spline_eval_deriv(spline, xi, acc);
    };
    doInterp(basis, type, func);
    return r;
}

QVector<double> HInterp::eval_deriv2(QPolygonF basis, QVector<double> xa, HInterpType type)
{
    QVector<double> r;
    auto func = [&](gsl_spline *spline, gsl_interp_accel *acc)
    {
        for (auto xi : xa)
            r << gsl_spline_eval_deriv2(spline, xi, acc);
    };
    doInterp(basis, type, func);
    return r;
}

double HInterp::eval_integ(QPolygonF basis, double a, double b, HInterpType type)
{
    double r;
    auto func = [&](gsl_spline *spline, gsl_interp_accel *acc)
    {
        r = gsl_spline_eval_integ(spline, a, b, acc);
    };
    doInterp(basis, type, func);
    return r;
}

HE_ALGORITHM_END_NAMESPACE

