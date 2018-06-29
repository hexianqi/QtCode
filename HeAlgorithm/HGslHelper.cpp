#include "HGslHelper.h"

HE_ALGORITHM_BEGIN_NAMESPACE

QPolygonF HGslHelper::join(QVector<double> x, QVector<double> y)
{
    Q_ASSERT(x.size() == y.size());

    QPolygonF r;
    for (int i = 0; i < x.size(); i++)
        r << QPointF(x[i], y[i]);
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

QVector<double> HGslHelper::fromGsl(gsl_vector *v)
{
    QVector<double> r(v->size);
    for (int i = 0; i < v->size; i++)
        r[i] = gsl_vector_get(v, i);
}

QVector<double> HGslHelper::fromGsl(gsl_matrix *m)
{
    QVector<double> r(m->tda);
    return r;
}


HE_ALGORITHM_END_NAMESPACE
