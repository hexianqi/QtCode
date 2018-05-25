#ifndef HSPECSETTING_P_H
#define HSPECSETTING_P_H

#include "HSpecSetting.h"
#include <QPolygonF>

HE_DATA_BEGIN_NAMESPACE

class HSpecSettingPrivate
{
public:
    bool isUsePlanck;
    bool isUseShield;
    QPolygonF stdEnergy;
    QVariantMap datas;
};

HE_DATA_END_NAMESPACE

#endif // HSPECSETTING_P_H
