/***************************************************************************************************
**      2022-07-25  HTestTricrystal
***************************************************************************************************/

#pragma once

#include "HeData/HTestData.h"

HE_USE_NAMESPACE

class HTestTricrystalPrivate;

class HTestTricrystal : public HTestData
{
    Q_DECLARE_PRIVATE(HTestTricrystal)

public:
    explicit HTestTricrystal();
    ~HTestTricrystal() override;
};
