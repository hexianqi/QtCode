/***************************************************************************************************
**      2022-02-10  HModel7000
***************************************************************************************************/

#pragma once

#include "HeController/HIntegrateModel.h"

HE_USE_NAMESPACE

class HModel7000Private;

class HModel7000 : public HIntegrateModel
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HModel7000)

public:
    explicit HModel7000(QObject *parent = nullptr);
    ~HModel7000() override;

public:
    QString typeName() override;

public:
    void syncTestData(quint32 type) override;
    void syncDeviceAll() override;
};



