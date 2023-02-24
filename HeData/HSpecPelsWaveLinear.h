/***************************************************************************************************
**      2018-06-19  HSpecPelsWave 像元波长数据类。
***************************************************************************************************/

#pragma once

#include "HSpecPelsWave.h"

HE_BEGIN_NAMESPACE

class HSpecPelsWaveLinearPrivate;

class HSpecPelsWaveLinear : public HSpecPelsWave
{
    Q_DECLARE_PRIVATE(HSpecPelsWaveLinear)

public:
    explicit HSpecPelsWaveLinear();

public:
    QString typeName() override;

public:
    double handle(double value) override;

protected:
    HSpecPelsWaveLinear(HSpecPelsWaveLinearPrivate &p);
};

HE_END_NAMESPACE
