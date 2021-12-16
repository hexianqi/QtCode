/***************************************************************************************************
**      2021-01-21  HDaXinStrategy
***************************************************************************************************/

#pragma once

#include "HeController/HAbstractActionStrategy.h"

HE_USE_NAMESPACE

class HDaXinStrategyPrivate;

class HDaXinStrategy : public HAbstractActionStrategy
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HDaXinStrategy)

public:
    explicit HDaXinStrategy(QObject *parent = nullptr);
    ~HDaXinStrategy() override;

public:
    QString typeName() override;

public:
    bool handle(HActionType action) override;

protected:
    HDaXinStrategy(HDaXinStrategyPrivate &p, QObject *parent = nullptr);
};



