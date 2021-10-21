/***************************************************************************************************
**      2019-10-24  HAbstractActionStrategy
***************************************************************************************************/

#pragma once

#include "IActionStrategy.h"

HE_CONTROLLER_BEGIN_NAMESPACE

class HAbstractActionStrategyPrivate;

class HE_CONTROLLER_EXPORT HAbstractActionStrategy : public QObject, public IActionStrategy
{
    Q_OBJECT

public:
    explicit HAbstractActionStrategy(QObject *parent = nullptr);

public:
    void initialize(QVariantMap param) override;

public:
    void setProtocol(IProtocol *) override;
    bool isSupport(HActionType action) override;

protected:
    HAbstractActionStrategy(HAbstractActionStrategyPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HAbstractActionStrategyPrivate> d_ptr;
};

HE_CONTROLLER_END_NAMESPACE
