#include "HMultiFit.h"
#include "HGslHelper.h"
#include "gsl/gsl_multifit.h"
#include <functional>

HE_ALGORITHM_BEGIN_NAMESPACE

const gsl_multifit_robust_type *toGsl(HMultiFit::RobustType type)
{
    switch (type)
    {
    case HMultiFit::Default:
        return gsl_multifit_robust_default;
    case HMultiFit::Bisquare:
        return gsl_multifit_robust_bisquare;
    case HMultiFit::Cauchy:
        return gsl_multifit_robust_cauchy;
    case HMultiFit::Fair:
        return gsl_multifit_robust_fair;
    case HMultiFit::Huber:
        return gsl_multifit_robust_huber;
    case HMultiFit::Ols:
        return gsl_multifit_robust_ols;
    case HMultiFit::Welsch:
        return gsl_multifit_robust_welsch;
    }
    return gsl_multifit_robust_default;
}

void fillAsPow(gsl_matrix *m, QVector<double> xa)
{
    size_t i, j;
    for (i = 0; i < m->size1; i++)
    {
        for (j = 0; j < m->size2; j++)
        {
            gsl_matrix_set(m, i, j, pow(xa[int(i)], j));
        }
    }
}

void fillAsPow(gsl_vector *v, double x)
{
    for (size_t i = 0; i < v->size; i++)
        gsl_vector_set(v, i, pow(x, i));
}

void doFit(QPolygonF basis, QVector<double> &ca, QVector<double> &cova, std::function<void(gsl_matrix *, gsl_vector *, gsl_vector *, gsl_matrix *)> func)
{
    QVector<double> xa, ya;
    HGslHelper::split(basis, xa, ya);

    auto p = size_t(ca.size());
    auto n = size_t(basis.size());
    auto x = gsl_matrix_alloc(n, p);
    auto y = gsl_vector_view_array(ya.data(), n);
    auto c = gsl_vector_alloc(p);
    auto cov = gsl_matrix_alloc(p, p);

    fillAsPow(x, xa);   // 可替换
    func(x, &y.vector, c, cov);
    ca = HGslHelper::fromGsl(c);
    cova = HGslHelper::fromGsl(cov);

    gsl_matrix_free(x);
    gsl_vector_free(c);
    gsl_matrix_free(cov);
}

void doEst(double x, QVector<double> ca, QVector<double> cova, std::function<void(gsl_vector *, gsl_vector *, gsl_matrix *)> func)
{
    auto p = size_t(ca.size());
    auto n = size_t(cova.size()) / p;
    auto cov = gsl_matrix_view_array(cova.data(), n, p);
    auto c = gsl_vector_view_array(ca.data(), p);
    auto xt = gsl_vector_alloc(p);

    fillAsPow(xt, x);   // 可替换
    func(xt, &c.vector, &cov.matrix);
    gsl_vector_free(xt);
}

void HMultiFit::linear(QPolygonF basis, QVector<double> &ca, QVector<double> &cova, double *chisq)
{
    auto work = gsl_multifit_linear_alloc(size_t(basis.size()), size_t(ca.size()));
    auto func = [&](gsl_matrix *x, gsl_vector *y, gsl_vector *c, gsl_matrix *cov) { gsl_multifit_linear(x, y, c, cov, chisq, work); };
    doFit(basis, ca, cova, func);
    gsl_multifit_linear_free(work);
}

void HMultiFit::linear(QPolygonF basis, QVector<double> wa, QVector<double> &ca, QVector<double> &cova, double *chisq)
{
    auto w = gsl_vector_view_array(wa.data(), size_t(wa.size()));
    auto work = gsl_multifit_linear_alloc(size_t(basis.size()), size_t(ca.size()));
    auto func = [&](gsl_matrix *x, gsl_vector *y, gsl_vector *c, gsl_matrix *cov) { gsl_multifit_wlinear(x, &w.vector, y, c, cov, chisq, work); };
    doFit(basis, ca, cova, func);
    gsl_multifit_linear_free(work);
}

void HMultiFit::linear_est(double x, QVector<double> ca, QVector<double> cova, double *y, double *y_err)
{
    auto func = [&](gsl_vector *xt, gsl_vector *c, gsl_matrix *cov) { gsl_multifit_linear_est(xt, c, cov, y, y_err); };
    doEst(x, ca, cova, func);
}

void HMultiFit::robust(QPolygonF basis, QVector<double> &ca, QVector<double> &cova, RobustType type)
{
    auto work = gsl_multifit_robust_alloc(toGsl(type), size_t(basis.size()), size_t(ca.size()));
    auto func = [&](gsl_matrix *x, gsl_vector *y, gsl_vector *c, gsl_matrix *cov) { gsl_multifit_robust(x, y, c, cov, work); };
    doFit(basis, ca, cova, func);
    gsl_multifit_robust_free(work);
}

void HMultiFit::robust_est(double x, QVector<double> ca, QVector<double> cova, double *y, double *y_err)
{
    auto func = [&](gsl_vector *xt, gsl_vector *c, gsl_matrix *cov) { gsl_multifit_robust_est(xt, c, cov, y, y_err); };
    doEst(x, ca, cova, func);
}

HE_ALGORITHM_END_NAMESPACE
