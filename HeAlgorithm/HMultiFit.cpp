#include "HMultiFit.h"
#include "HGslHelper.h"
#include "gsl/gsl_multifit.h"
#include <functional>

HE_ALGORITHM_BEGIN_NAMESPACE

const gsl_multifit_robust_type *toGsl(HRobustType type)
{
    switch (type)
    {
    case Default:
        return gsl_multifit_robust_default;
    case Bisquare:
        return gsl_multifit_robust_bisquare;
    case Cauchy:
        return gsl_multifit_robust_cauchy;
    case Fair:
        return gsl_multifit_robust_fair;
    case Huber:
        return gsl_multifit_robust_huber;
    case Ols:
        return gsl_multifit_robust_ols;
    case Welsch:
        return gsl_multifit_robust_welsch;
    default:
        return gsl_multifit_robust_default;
    }
}

void fillAsPow(gsl_matrix *m, QVector<double> x)
{
    uint i,j;
    for (i = 0; i < m->size1; i++)
        for (j = 0; j < m->size2; j++)
            gsl_matrix_set(m, i, j, pow(x[i], j));
}

void fillAsPow(gsl_vector *v, double x)
{
    for (uint i = 0; i < v->size; i++)
        gsl_vector_set(v, i, pow(x, i));
}

void doFit(QPolygonF basis, QVector<double> &c, QVector<double> &cov, std::function<void(gsl_matrix *, gsl_vector *, gsl_vector *, gsl_matrix *)> func)
{
    QVector<double> x, y;
    HGslHelper::split(basis, x, y);

    auto p = c.size();
    auto n = basis.size();
    auto xt = gsl_matrix_alloc(n, p);
    auto yt = gsl_vector_view_array(y.data(), n);
    auto ct = gsl_vector_alloc(p);
    auto covt = gsl_matrix_alloc(p, p);

    fillAsPow(xt, x);
    func(xt, &yt.vector, ct, covt);
    c = HGslHelper::fromGsl(ct);
    cov = HGslHelper::fromGsl(covt);

    gsl_matrix_free(xt);
    gsl_vector_free(ct);
    gsl_matrix_free(covt);
}

void doEst(double x, QVector<double> c, QVector<double> cov, std::function<void(gsl_vector *, gsl_vector *, gsl_matrix *)> func)
{
    auto p = c.size();
    auto n = cov.size() / p;
    auto covt = gsl_matrix_view_array(cov.data(), n, p);
    auto ct = gsl_vector_view_array(c.data(), p);
    auto xt = gsl_vector_alloc(p);

    fillAsPow(xt, x);
    func(xt, &ct.vector, &covt.matrix);

    gsl_vector_free(xt);
}

HMultiFit::HMultiFit()
{
}

void HMultiFit::linear(QPolygonF basis, QVector<double> &c, QVector<double> &cov, double *chisq)
{
    auto work = gsl_multifit_linear_alloc(basis.size(), c.size());
    auto func = [&](gsl_matrix *xt, gsl_vector *yt, gsl_vector *ct, gsl_matrix *covt)
    {
        gsl_multifit_linear(xt, yt, ct, covt, chisq, work);
    };
    doFit(basis, c, cov, func);
    gsl_multifit_linear_free(work);
}

void HMultiFit::linear(QPolygonF basis, QVector<double> w, QVector<double> &c, QVector<double> &cov, double *chisq)
{
    auto wt = gsl_vector_view_array(w.data(), w.size());
    auto work = gsl_multifit_linear_alloc(basis.size(), c.size());
    auto func = [&](gsl_matrix *xt, gsl_vector *yt, gsl_vector *ct, gsl_matrix *covt)
    {
        gsl_multifit_wlinear(xt, &wt.vector, yt, ct, covt, chisq, work);
    };
    doFit(basis, c, cov, func);
    gsl_multifit_linear_free(work);
}

void HMultiFit::linearEst(double x, QVector<double> c, QVector<double> cov, double *y, double *y_err)
{
    auto func = [&](gsl_vector *xt, gsl_vector *ct, gsl_matrix *covt)
    {
        gsl_multifit_linear_est(xt, ct, covt, y, y_err);
    };
    doEst(x, c, cov, func);
}

void HMultiFit::robust(QPolygonF basis, QVector<double> &c, QVector<double> &cov, HRobustType type)
{
    auto work = gsl_multifit_robust_alloc(toGsl(type), basis.size(), c.size());
    auto func = [&](gsl_matrix *xt, gsl_vector *yt, gsl_vector *ct, gsl_matrix *covt)
    {
        gsl_multifit_robust(xt, yt, ct, covt, work);
    };
    doFit(basis, c, cov, func);
    gsl_multifit_robust_free(work);
}

void HMultiFit::robustEst(double x, QVector<double> c, QVector<double> cov, double *y, double *y_err)
{
    auto func = [&](gsl_vector *xt, gsl_vector *ct, gsl_matrix *covt)
    {
        gsl_multifit_robust_est(xt, ct, covt, y, y_err);
    };
    doEst(x, c, cov, func);
}

HE_ALGORITHM_END_NAMESPACE
