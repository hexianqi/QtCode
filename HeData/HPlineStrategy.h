/***************************************************************************************************
**      2023-03-09  HPlineStrategy
***************************************************************************************************/

#pragma once

#include "HAbstractLinearStrategy.h"

HE_BEGIN_NAMESPACE

class HPlineStrategyPrivate;

class HPlineStrategy : public HAbstractLinearStrategy
{
    Q_DECLARE_PRIVATE(HPlineStrategy)

public:
    explicit HPlineStrategy();

public:
    QString typeName() override;

public:
    double estimate(double) override;

protected:
    HPlineStrategy(HPlineStrategyPrivate &);
};

HE_END_NAMESPACE

