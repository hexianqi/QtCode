#include "HGslHelper.h"

HE_ALGORITHM_BEGIN_NAMESPACE

QPolygonF HGslHelper::join(QVector<double> xa, QVector<double> y)
{
    Q_ASSERT(xa.size() == y.size());

    QPolygonF r;
    for (int i = 0; i < xa.size(); i++)
        r << QPointF(xa[i], y[i]);
    return r;
}

void HGslHelper::split(QPolygonF poly, QVector<double> &x, QVector<double> &y)
{
    x.clear();
    y.clear();
    for (auto p : poly)
    {
        x << p.x();
        y << p.y();
    }
}

QPointF HGslHelper::formGsl(gsl_complex z)
{
    return QPointF(GSL_REAL(z), GSL_IMAG(z));
}

QPolygonF HGslHelper::formGsl(QVector<gsl_complex> z)
{
    QPolygonF r;
    for (auto i : z)
        r << formGsl(i);
    return r;
}

QVector<double> HGslHelper::fromGsl(gsl_vector *v)
{
    QVector<double> r;
    for (uint i = 0; i < v->size; i++)
        r << gsl_vector_get(v, i);
    return r;
}

QVector<double> HGslHelper::fromGsl(gsl_matrix *m)
{
    QVector<double> r;
    for (uint i = 0; i < m->size1; i++)
    {
        for (uint j = 0; j < m->size2; j++)
            r << gsl_matrix_get(m, i, j);
    }
    return r;
}

HE_ALGORITHM_END_NAMESPACE
