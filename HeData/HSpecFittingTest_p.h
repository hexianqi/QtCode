#pragma once

#include "HSpecFittingTest.h"
#include "HSpecFitting_p.h"

HE_BEGIN_NAMESPACE

class HSpecFittingTestPrivate : public HSpecFittingPrivate
{
public:
    QList<QPolygonF> allPoints;
};

HE_END_NAMESPACE
