#pragma once

#include "HSpecFittingPolynom.h"
#include "HSpecFitting_p.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecFittingPolynomPrivate : public HSpecFittingPrivate
{
public:
    QVector<double> ca;
    QVector<double> cova;
};

HE_DATA_END_NAMESPACE
