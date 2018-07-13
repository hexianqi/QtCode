#ifndef HSPECFITTING_P_H
#define HSPECFITTING_P_H

#include "HSpecFitting.h"
#include "HAbstractCalibrateItem_p.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecFittingPrivate : public HAbstractCalibrateItemPrivate
{
public:
    QList<double> coefficients;
};

HE_DATA_END_NAMESPACE

#endif // HSPECFITTING_P_H
