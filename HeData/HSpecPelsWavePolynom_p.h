#pragma once

#include "HSpecPelsWavePolynom.h"
#include "HSpecPelsWave_p.h"

HE_BEGIN_NAMESPACE

class HSpecPelsWavePolynomPrivate : public HSpecPelsWavePrivate
{
public:
    QVector<double> ca;
    QVector<double> cova;
};

HE_END_NAMESPACE

