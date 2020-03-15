#include "HGslHelper.h"

HE_ALGORITHM_BEGIN_NAMESPACE

QPolygonF HGslHelper::join(QVector<double> xa, QVector<double> ya)
{
    Q_ASSERT(xa.size() == ya.size());

    QPolygonF r;
    for (int i = 0; i < xa.size(); i++)
        r << QPointF(xa[i], ya[i]);
    return r;
}

void HGslHelper::split(QPolygonF poly, QVector<double> &xa, QVector<double> &ya)
{
    xa.clear();
    ya.clear();
    for (auto p : poly)
    {
        xa << p.x();
        ya << p.y();
    }
}

QPointF HGslHelper::formGsl(gsl_complex z)
{
    return QPointF(GSL_REAL(z), GSL_IMAG(z));
}

QPolygonF HGslHelper::formGsl(QVector<gsl_complex> za)
{
    QPolygonF r;
    for (auto zi : za)
        r << formGsl(zi);
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
