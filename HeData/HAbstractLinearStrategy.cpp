#include "HAbstractLinearStrategy_p.h"

HE_BEGIN_NAMESPACE

HAbstractLinearStrategy::HAbstractLinearStrategy() :
    d_ptr(new HAbstractLinearStrategyPrivate)
{
}

HAbstractLinearStrategy::HAbstractLinearStrategy(HAbstractLinearStrategyPrivate &p) :
    d_ptr(&p)
{
}

HAbstractLinearStrategy::~HAbstractLinearStrategy()
{
}

void HAbstractLinearStrategy::initialize(QVariantMap param)
{
    if (param.contains("datas"))
        d_ptr->datas = param.value("datas").toMap();
}

void HAbstractLinearStrategy::setData(QPolygonF points, QVariantMap param)
{
    d_ptr->points = points;
    d_ptr->datas = param;
}

HE_END_NAMESPACE
