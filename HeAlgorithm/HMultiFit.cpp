#include "HMultiFit.h"
#include "HGslHelper.h"
#include "gsl/gsl_multifit.h"

HE_ALGORITHM_BEGIN_NAMESPACE

HMultiFit::HMultiFit()
{

}

void HMultiFit::linear(QPolygonF basis, QVector<double> w, QVector<double> &c, QVector<double> &cov, double *chisq)
{
    int i,j;
    QVector<double> xt, yt;
    HGslHelper::split(basis, xt, yt);

    auto n = basis.size();
    auto p = c.size();
    auto x = gsl_matrix_alloc(n, p);
    auto y = gsl_vector_view_array(yt.data(), n);
    auto wt = gsl_vector_view_array(w.data(), n);
    auto ct = gsl_vector_alloc(p);
    auto covt = gsl_matrix_alloc(p, p);
    auto work = gsl_multifit_linear_alloc(n, p);

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < p; j++)
            gsl_matrix_set(x, i, j, pow(xt[i], j));
    }
    gsl_multifit_wlinear(x, &wt.vector, &y.vector, ct, covt, chisq, work);

    c = HGslHelper::fromGsl(ct);

    gsl_matrix_free(x);
    gsl_vector_free(ct);
    gsl_vector_free(ct);
    gsl_matrix_free(covt);
    gsl_multifit_linear_free (work);
}

HE_ALGORITHM_END_NAMESPACE
