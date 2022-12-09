/***************************************************************************************************
**      2022-12-06  HStrategy1000RGB
***************************************************************************************************/

#pragma once

#include "HeController/HAbstractActionStrategy.h"

HE_USE_NAMESPACE

class HStrategy1000RGBPrivate;

class HStrategy1000RGB : public HAbstractActionStrategy
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HStrategy1000RGB)

public:
    explicit HStrategy1000RGB(QObject *parent = nullptr);
    ~HStrategy1000RGB() override;

public:
    QString typeName() override;

public:
    bool handle(HActionType action) override;
};



