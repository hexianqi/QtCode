#pragma once

#include "HBattery.h"
#include "HAnimationProgress_p.h"

HE_BEGIN_NAMESPACE

class HBatteryPrivate : public HAnimationProgressPrivate
{
public:
    double alarmValue = 20;
    int borderRadius = 8;
    int backgroundRadius = 5;
    int headRadius = 3;
    QColor borderColorStart = QColor(100, 100, 100);
    QColor borderColorEnd = QColor(80, 80, 80);
    QColor alarmColorStart = QColor(250, 118, 113);
    QColor alarmColorEnd = QColor(204, 38, 38);
    QColor normalColorStart = QColor(50, 205, 51);
    QColor normalColorEnd = QColor(60, 179, 133);
};

HE_END_NAMESPACE
