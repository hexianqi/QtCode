/***************************************************************************************************
**      2021-03-17  HPowerFactorStrategy
***************************************************************************************************/

#pragma once

#include "HAbstractActionStrategy.h"

HE_BEGIN_NAMESPACE

class HPowerFactorStrategyPrivate;

class HPowerFactorStrategy : public HAbstractActionStrategy
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HPowerFactorStrategy)

public:
    explicit HPowerFactorStrategy(QObject *parent = nullptr);
    ~HPowerFactorStrategy() override;

public:
    QString typeName() override;

public:
    bool handle(HActionType action) override;

protected:
    HPowerFactorStrategy(HPowerFactorStrategyPrivate &p, QObject *parent = nullptr);
};

HE_END_NAMESPACE

