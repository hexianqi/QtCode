/***************************************************************************************************
**      2022-04-02  HMotorStrategy
***************************************************************************************************/

#pragma once

#include "HAbstractActionStrategy.h"

HE_BEGIN_NAMESPACE

class HMotorStrategyPrivate;

class HMotorStrategy : public HAbstractActionStrategy
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HMotorStrategy)

public:
    explicit HMotorStrategy(QObject *parent = nullptr);
    ~HMotorStrategy() override;

public:
    QString typeName() override;

public:
    bool handle(HActionType action) override;

protected:
    HMotorStrategy(HMotorStrategyPrivate &p, QObject *parent = nullptr);
};

HE_END_NAMESPACE

