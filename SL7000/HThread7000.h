/***************************************************************************************************
**      2022-02-02  HThread7000
***************************************************************************************************/

#pragma once

#include "HeController/HIntegrateThread.h"

HE_USE_NAMESPACE

class HThread7000Private;

class HThread7000 : public HIntegrateThread
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HThread7000)

public:
    explicit HThread7000(QObject *parent = nullptr);
    ~HThread7000() override;

public:
    QString typeName() override;

protected:
    void init() override;
};
