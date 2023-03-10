#include "HPlineStrategy_p.h"
#include "HeAlgorithm/HMath.h"

HE_BEGIN_NAMESPACE

HPlineStrategy::HPlineStrategy() :
    HAbstractLinearStrategy(*new HPlineStrategyPrivate)
{
}

HPlineStrategy::HPlineStrategy(HPlineStrategyPrivate &p) :
    HAbstractLinearStrategy(p)
{
}

QString HPlineStrategy::typeName()
{
    return "HPlineStrategy";
}

double HPlineStrategy::estimate(double value)
{
    Q_D(HPlineStrategy);
    if (d->points.size() < 3)
        return d->datas.value("[线性默认值]", 0.0).toDouble();
    return HMath::interpolate(value, d->points);
}

HE_END_NAMESPACE
