#ifndef HBATTERY_P_H
#define HBATTERY_P_H

#include "HBattery.h"
#include "HAnimationProgress_p.h"

class QPropertyAnimation;

HE_CONTROL_BEGIN_NAMESPACE

class HBatteryPrivate : public HAnimationProgressPrivate
{
public:
    double alarmValue = 20;
    QColor borderColorStart = QColor(100, 100, 100);
    QColor borderColorEnd = QColor(80, 80, 80);
    QColor alarmColorStart = QColor(250, 118, 113);
    QColor alarmColorEnd = QColor(204, 38, 38);
    QColor normalColorStart = QColor(50, 205, 51);
    QColor normalColorEnd = QColor(60, 179, 133);
};

HE_CONTROL_END_NAMESPACE
#endif // HBATTERY_P_H
