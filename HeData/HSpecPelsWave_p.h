#ifndef HSPECPELSWAVE_P_H
#define HSPECPELSWAVE_P_H

#include "HSpecPelsWave.h"
#include "HAbstractCalibrateItem_p.h"
#include <QPolygonF>

HE_DATA_BEGIN_NAMESPACE

class HSpecPelsWavePrivate : public HAbstractCalibrateItemPrivate
{
public:
    QPolygonF pelsWave;
};

HE_DATA_END_NAMESPACE

#endif // HSPECPELSWAVE_P_H
