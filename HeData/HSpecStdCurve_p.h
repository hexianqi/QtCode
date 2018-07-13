#ifndef HSPECSTDCURVE_P_H
#define HSPECSTDCURVE_P_H

#include "HSpecStdCurve.h"
#include "HAbstractCalibrateItem_p.h"
#include <QVector>

HE_DATA_BEGIN_NAMESPACE

class HSpecStdCurvePrivate : public HAbstractCalibrateItemPrivate
{
public:
    QVector<double> curve;
};

HE_DATA_END_NAMESPACE

#endif // HSPECSTDCURVE_P_H
