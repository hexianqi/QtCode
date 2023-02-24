/***************************************************************************************************
**      2023-02-22  HSpecPelsWavePolynom
***************************************************************************************************/

#pragma once

#include "HSpecPelsWave.h"

HE_BEGIN_NAMESPACE

class HSpecPelsWavePolynomPrivate;

class HSpecPelsWavePolynom : public HSpecPelsWave
{
    Q_DECLARE_PRIVATE(HSpecPelsWavePolynom)

public:
    explicit HSpecPelsWavePolynom();

public:
    QString typeName() override;

public:
    void restoreDefault() override;
    void setPoints(const QPolygonF &value) override;
    double handle(double value) override;

protected:
    HSpecPelsWavePolynom(HSpecPelsWavePolynomPrivate &);

protected:
    void linear();
    double linearEst(double value);
};

HE_END_NAMESPACE

