/***************************************************************************************************
**      2019-10-24  HAbstractActionStrategy
***************************************************************************************************/

#ifndef HABSTRACTACTIONSTRATEGY_H
#define HABSTRACTACTIONSTRATEGY_H

#include "IActionStrategy.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HAbstractActionStrategyPrivate;

class HAbstractActionStrategy : public IActionStrategy
{
    Q_OBJECT

public:
    explicit HAbstractActionStrategy(QObject *parent = nullptr);

public:
    void initialize(QVariantMap param) override;

public:
    bool isSupport(HActionType action) override;

protected:
    HAbstractActionStrategy(HAbstractActionStrategyPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HAbstractActionStrategyPrivate> d_ptr;
};

HE_CONTROLLER_END_NAMESPACE

#endif // HABSTRACTACTIONSTRATEGY_H
