#ifndef HSPECFITTINGTEST_P_H
#define HSPECFITTINGTEST_P_H

#include "HSpecFittingTest.h"
#include "HSpecFitting_p.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecFittingTestPrivate : public HSpecFittingPrivate
{
public:
    QList<QPolygonF> allFittingPoints;
};

HE_DATA_END_NAMESPACE

#endif // HSPECFITTINGTEST_P_H
