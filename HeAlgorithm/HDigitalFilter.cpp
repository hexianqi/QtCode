#include "HDigitalFilter.h"
//#include "gsl/gsl_filter.h"
#include <QVector>

HE_ALGORITHM_BEGIN_NAMESPACE

//QVector<double> fromGsl(gsl_vector *v)
//{
//    QVector<double> r(v->size);
//    for (int i = 0; i < v->size; i++)
//        r[i] = gsl_vector_get(v, i);
//    return r;
//}

//QVector<double> HDigitalFilter::gaussian(HFilterEndType type, int k, double alpha, int order, QVector<double> x)
//{
//    auto y = gsl_vector_alloc(x.size());
//    auto w = gsl_filter_gaussian_alloc(k);
//    gsl_filter_gaussian(gsl_filter_end_t(type), alpha, order, x, z, w);
//    auto r = fromGsl(z);
//    gsl_filter_gaussian_free(w);
//    gsl_vector_free(y);
//    return r;
//}

//QVector<double> HDigitalFilter::gaussianKernel(int k, double alpha, int order, int normalize)
//{
//    auto kernel = gsl_vector_alloc(k);
//    gsl_filter_gaussian_kernel(alpha, order, normalize, kernel);
//    auto r = fromGsl(kernel);
//    gsl_vector_free(kernel);
//    return r;
//}

HE_ALGORITHM_END_NAMESPACE
