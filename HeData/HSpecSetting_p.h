#ifndef HSPECSETTING_P_H
#define HSPECSETTING_P_H

#include "HSpecSetting.h"
#include "HAbstractCalibrateItem_p.h"
#include <QPolygonF>

HE_DATA_BEGIN_NAMESPACE

class HSpecSettingPrivate : public HAbstractCalibrateItemPrivate
{
public:
    bool isUsePlanck;
    bool isUseShield;
    QPolygonF stdEnergy;
};

HE_DATA_END_NAMESPACE

#endif // HSPECSETTING_P_H
