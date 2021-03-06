#include "HInterp2D.h"
#include "gsl/gsl_spline2d.h"
#include <functional>

HE_ALGORITHM_BEGIN_NAMESPACE

const gsl_interp2d_type *toGsl(HInterp2DType type)
{
    switch (type)
    {
    case Bilinear:
        return gsl_interp2d_bilinear;
    case Bicubic:
        return gsl_interp2d_bicubic;
    default:
        return gsl_interp2d_bilinear;
    }
}

void doInterp(QVector<double> xa, QVector<double> ya, QVector<double> za, HInterp2DType type, std::function<void(gsl_spline2d *, gsl_interp_accel *, gsl_interp_accel *)> func)
{
    auto t = toGsl(type);
    size_t xsize = xa.size();
    size_t ysize = ya.size();
    size_t zsize = za.size();
    Q_ASSERT(zsize == xsize * ysize && xsize >= t->min_size && ysize >= t->min_size);

    auto spline = gsl_spline2d_alloc(t, xsize, ysize);
    auto xacc = gsl_interp_accel_alloc();
    auto yacc = gsl_interp_accel_alloc();
    gsl_spline2d_init(spline, xa.data(), ya.data(), za.data(), xsize, ysize);
    spline->interp_object.xmin = __DBL_MIN__;
    spline->interp_object.xmax = __DBL_MAX__;
    spline->interp_object.ymin = __DBL_MIN__;
    spline->interp_object.ymax = __DBL_MAX__;
    func(spline, xacc, yacc);
    gsl_spline2d_free(spline);
    gsl_interp_accel_free(xacc);
    gsl_interp_accel_free(yacc);
}

double HInterp2D::eval(QVector<double> xa, QVector<double> ya, QVector<double> za, double x, double y, HeAlgorithm::HInterp2DType type)
{
    double r;
    auto func = [&](gsl_spline2d *spline, gsl_interp_accel *xacc, gsl_interp_accel *yacc)
    {
        r = gsl_spline2d_eval(spline, x, y, xacc, yacc);
    };
    doInterp(xa, ya, za, type, func);
    return r;
}

double HInterp2D::eval_deriv_x(QVector<double> xa, QVector<double> ya, QVector<double> za, double x, double y, HInterp2DType type)
{
    double r;
    auto func = [&](gsl_spline2d *spline, gsl_interp_accel *xacc, gsl_interp_accel *yacc)
    {
        r = gsl_spline2d_eval_deriv_x(spline, x, y, xacc, yacc);
    };
    doInterp(xa, ya, za, type, func);
    return r;
}

double HInterp2D::eval_deriv_y(QVector<double> xa, QVector<double> ya, QVector<double> za, double x, double y, HInterp2DType type)
{
    double r;
    auto func = [&](gsl_spline2d *spline, gsl_interp_accel *xacc, gsl_interp_accel *yacc)
    {
        r = gsl_spline2d_eval_deriv_y(spline, x, y, xacc, yacc);
    };
    doInterp(xa, ya, za, type, func);
    return r;
}

double HInterp2D::eval_deriv_xx(QVector<double> xa, QVector<double> ya, QVector<double> za, double x, double y, HInterp2DType type)
{
    double r;
    auto func = [&](gsl_spline2d *spline, gsl_interp_accel *xacc, gsl_interp_accel *yacc)
    {
        r = gsl_spline2d_eval_deriv_xx(spline, x, y, xacc, yacc);
    };
    doInterp(xa, ya, za, type, func);
    return r;
}

double HInterp2D::eval_deriv_yy(QVector<double> xa, QVector<double> ya, QVector<double> za, double x, double y, HInterp2DType type)
{
    double r;
    auto func = [&](gsl_spline2d *spline, gsl_interp_accel *xacc, gsl_interp_accel *yacc)
    {
        r = gsl_spline2d_eval_deriv_yy(spline, x, y, xacc, yacc);
    };
    doInterp(xa, ya, za, type, func);
    return r;
}

double HInterp2D::eval_deriv_xy(QVector<double> xa, QVector<double> ya, QVector<double> za, double x, double y, HInterp2DType type)
{
    double r;
    auto func = [&](gsl_spline2d *spline, gsl_interp_accel *xacc, gsl_interp_accel *yacc)
    {
        r = gsl_spline2d_eval_deriv_xy(spline, x, y, xacc, yacc);
    };
    doInterp(xa, ya, za, type, func);
    return r;
}

HE_ALGORITHM_END_NAMESPACE
