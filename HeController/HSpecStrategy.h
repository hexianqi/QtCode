/***************************************************************************************************
**      2019-10-24  HSpecStrategy 光谱动作策略。
***************************************************************************************************/

#ifndef HSPECSTRATEGY_H
#define HSPECSTRATEGY_H

#include "HAbstractActionStrategy.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HSpecStrategyPrivate;

class HSpecStrategy : public HAbstractActionStrategy
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecStrategy)

public:
    explicit HSpecStrategy(QObject *parent = nullptr);
    ~HSpecStrategy() override;

public:
    QString typeName() override;

public:
    HErrorType handle(HActionType action) override;

protected:
    HSpecStrategy(HSpecStrategyPrivate &p, QObject *parent = nullptr);
};

HE_CONTROLLER_END_NAMESPACE

#endif // HSPECSTRATEGY_H
