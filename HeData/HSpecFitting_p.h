#ifndef HSPECFITTING_P_H
#define HSPECFITTING_P_H

#include "HSpecFitting.h"

HE_DATA_BEGIN_NAMESPACE

class HSpecFittingPrivate
{
public:
    QVariantMap datas;
    QList<double> coefficients;
};

HE_DATA_END_NAMESPACE

#endif // HSPECFITTING_P_H
