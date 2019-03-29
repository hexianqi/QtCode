#include "HSpecFittingLinear_p.h"
#include "HeAlgorithm/HInterp.h"

HE_ALGORITHM_USE_NAMESPACE

HE_DATA_BEGIN_NAMESPACE

HSpecFittingLinear::HSpecFittingLinear()
    : HSpecFitting(*new HSpecFittingLinearPrivate)
{
    restoreDefault();
}

HSpecFittingLinear::HSpecFittingLinear(HSpecFittingLinearPrivate &p)
    : HSpecFitting(p)
{
}

HSpecFittingLinear::~HSpecFittingLinear()
{
}

QString HSpecFittingLinear::typeName()
{
    return "HSpecFittingLinear";
}

double HSpecFittingLinear::calcRate(double value)
{
    Q_D(HSpecFittingLinear);
    if (d->fittingPoints.size() < 3)
        return 1;

    auto range = data("[光谱拟合有效范围]").toPointF();
    value = qBound(range.x(), value, range.y());
    return HInterp::eval(d->fittingPoints, value, HInterpType::Cspline);
}

HE_DATA_END_NAMESPACE
