#include "HGslHelper.h"
#include "gsl/gsl_complex_math.h"

HE_BEGIN_NAMESPACE

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

QPointF HGslHelper::toPointF(gsl_complex z)
{
    return {GSL_REAL(z), GSL_IMAG(z)};
}

QPolygonF HGslHelper::toPolygonF(QVector<gsl_complex> z)
{
    QPolygonF r;
    for (auto i : z)
        r << toPointF(i);
    return r;
}

QVector<double> HGslHelper::toVector(gsl_vector *v)
{
    QVector<double> r;
    for (uint i = 0; i < v->size; i++)
        r << gsl_vector_get(v, i);
    return r;
}

QVector<double> HGslHelper::toVector(gsl_matrix *m)
{
    QVector<double> r;
    for (uint i = 0; i < m->size1; i++)
    {
        for (uint j = 0; j < m->size2; j++)
            r << gsl_matrix_get(m, i, j);
    }
    return r;
}

void HGslHelper::fill(gsl_matrix *m, QVector<double> value)
{
    uint i, j;
    int k = 0;
    double v;
    for (i = 0; i < m->size1; i++)
    {
        for (j = 0; j < m->size2; j++)
        {
            v = k < value.size() ? value.at(k) : 0.0;
            gsl_matrix_set(m, i, j, v);
            k++;
        }
    }
}

gsl_complex HGslHelper::fromPoint(double x, double y)
{
    return gsl_complex_rect(x, y);
}

gsl_complex HGslHelper::fromPolar(double r, double theta)
{
    return gsl_complex_polar(r, theta);
}

HE_END_NAMESPACE
