/***************************************************************************************************
**      2019-10-24  HElecStrategy 电动作策略。
***************************************************************************************************/

#pragma once

#include "HAbstractActionStrategy.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HElecStrategyPrivate;

class HElecStrategy : public HAbstractActionStrategy
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HElecStrategy)

public:
    explicit HElecStrategy(QObject *parent = nullptr);
    ~HElecStrategy() override;

public:
    QString typeName() override;

public:
    bool handle(HActionType action) override;

protected:
    HElecStrategy(HElecStrategyPrivate &p, QObject *parent = nullptr);
};

HE_CONTROLLER_END_NAMESPACE
