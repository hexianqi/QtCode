/***************************************************************************************************
**      2022-02-08  HKeyenceStrategy
***************************************************************************************************/

#pragma once

#include "HeController/HAbstractActionStrategy.h"

HE_USE_NAMESPACE

class HKeyenceStrategyPrivate;

class HKeyenceStrategy : public HAbstractActionStrategy
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HKeyenceStrategy)

public:
    explicit HKeyenceStrategy(QObject *parent = nullptr);
    ~HKeyenceStrategy() override;

public:
    QString typeName() override;

public:
    bool handle(HActionType action) override;

protected:
    HKeyenceStrategy(HKeyenceStrategyPrivate &p, QObject *parent = nullptr);
};



