#pragma once

#include "HPolynomStrategy.h"
#include "HAbstractLinearStrategy_p.h"

HE_BEGIN_NAMESPACE

class HPolynomStrategyPrivate : public HAbstractLinearStrategyPrivate
{
public:
    QVector<double> ca;
    QVector<double> cova;
};

HE_END_NAMESPACE

