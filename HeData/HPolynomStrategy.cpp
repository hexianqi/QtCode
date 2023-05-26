#include "HPolynomStrategy_p.h"
#include "HeAlgorithm/HMultiFit.h"
#include "HeAlgorithm/HMath.h"

HE_BEGIN_NAMESPACE

HPolynomStrategy::HPolynomStrategy() :
    HAbstractLinearStrategy(*new HPolynomStrategyPrivate)
{
}

HPolynomStrategy::HPolynomStrategy(HPolynomStrategyPrivate &p) :
    HAbstractLinearStrategy(p)
{
}

QString HPolynomStrategy::typeName()
{
    return "HPolynomStrategy";
}

void HPolynomStrategy::setData(QPolygonF points, QVariantMap param)
{
    HAbstractLinearStrategy::setData(points, param);
    linear();
}

double HPolynomStrategy::estimate(double value)
{
    Q_D(HPolynomStrategy);
    auto offset = d->datas.value("[线性偏差]", -0.0).toDouble();
    auto range = d->datas.value("[线性有效范围]").toPointF();
    if (offset <= 0.0 || (value >= range.x() && value <= range.y()))
        return linearEst(value);

    double x1, x2, y1, y2;
    if (value < range.x())
    {
        x1 = range.x();
        x2 = range.x() + offset;
    }
    else
    {
        x1 = range.y() - offset;
        x2 = range.y();
    }

    y1 = linearEst(x1);
    y2 = linearEst(x2);
    return HMath::interpolate(value, x1, y1, x2, y2);
}

void HPolynomStrategy::linear()
{
    Q_D(HPolynomStrategy);
    d->ca.clear();
    d->cova.clear();
    if (d->points.isEmpty())
        return;
    double chisq;
    auto size = qMin(d->datas.value("[线性多项式项数]", 7).toInt(), d->points.size());
    d->datas["[线性有效范围]"] = QPointF(d->points.first().x(), d->points.last().x());
    if (size > 1)
    {
        d->ca.resize(size);
        HMultiFit::linear(d->points, d->ca, d->cova, &chisq);
    }
}

double HPolynomStrategy::linearEst(double value)
{
    Q_D(HPolynomStrategy);
    if (d->ca.size() < 2)
        return d->datas.value("[线性默认值]", 0.0).toDouble();
    double y, error;
    HMultiFit::linear_est(value, d->ca, d->cova, &y, &error);
    return  y;
}

HE_END_NAMESPACE
