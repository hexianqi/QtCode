/***************************************************************************************************
**      2021-01-25  HModel2100DC
***************************************************************************************************/

#pragma once

#include "HeController/HSpecModel.h"

HE_USE_NAMESPACE

class HModel2100DCPrivate;

class HModel2100DC : public HSpecModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HModel2100DC)

public:
    explicit HModel2100DC(QObject *parent = nullptr);
    ~HModel2100DC() override;

public:
    QString typeName() override;

public:
    void syncDeviceAll() override;

protected:
    HModel2100DC(HModel2100DCPrivate &p, QObject *parent = nullptr);
};



