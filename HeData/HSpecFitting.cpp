#include "HSpecFitting_p.h"

HE_BEGIN_NAMESPACE

HSpecFitting::HSpecFitting() :
    HAbstractDataItem(*new HSpecFittingPrivate)
{
    init();
}

HSpecFitting::HSpecFitting(HSpecFittingPrivate &p) :
    HAbstractDataItem(p)
{
}

void HSpecFitting::clear()
{
    Q_D(HSpecFitting);
    d->points.clear();
}

void HSpecFitting::setPoints(QPolygonF value)
{
    Q_D(HSpecFitting);
    setData("[光谱拟合取样次数]", value.size());
    setData("[光谱拟合有效范围]", QPointF(value.first().x(), value.last().x()));

    int i;
    double t = 0.0;
    QVector<double> y;

    for (i = 0; i < value.size(); i++)
    {
        y << value[i].x() / value[i].y();
        t = qMax(t, y[i]);
    }
    for (i = 0; i < value.size(); i++)
        value[i].setY(y[i] / t);
    d->points = value;
}

QPolygonF HSpecFitting::points()
{
    Q_D(HSpecFitting);
    return d->points;
}

QPolygonF HSpecFitting::curve(double interval)
{
    auto r = data("[光谱拟合有效范围]").toPointF();
    QPolygonF p;
    for (double d = r.x() - 100; d < r.y() + 100; d += interval)
        p << QPointF(d, calcRate(d));
    return p;
}

QVector<double> HSpecFitting::handle(QVector<double> value, bool abovezero)
{
    QVector<double> r;
    for (auto v : value)
        r << handle(v, abovezero);
    return r;
}

void HSpecFitting::init()
{
    Q_D(HSpecFitting);
    setData("[光谱拟合基准像元]", 1000);
    setData("[光谱拟合取样次数]", 100);
    setData("[光谱拟合积分时间范围]", QPointF(10, 100));
    setData("[光谱拟合有效范围]", QPointF(0, 65535));
    d->points.clear();
}

double HSpecFitting::handle(double value, bool abovezero)
{
    auto rate = calcRate(value);
    value = value / rate;
    if (abovezero)
        value = qMax(0.0, value);
    return value;
}

HE_END_NAMESPACE
