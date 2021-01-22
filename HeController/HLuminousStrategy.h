/***************************************************************************************************
**      2020-05-26  HLuminousStrategy 光动作策略。
***************************************************************************************************/

#pragma once

#include "HAbstractActionStrategy.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HLuminousStrategyPrivate;

class HLuminousStrategy : public HAbstractActionStrategy
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HLuminousStrategy)

public:
    explicit HLuminousStrategy(QObject *parent = nullptr);
    ~HLuminousStrategy() override;

public:
    QString typeName() override;

public:
    bool handle(HActionType action) override;

protected:
    HLuminousStrategy(HLuminousStrategyPrivate &p, QObject *parent = nullptr);
};

HE_CONTROLLER_END_NAMESPACE

