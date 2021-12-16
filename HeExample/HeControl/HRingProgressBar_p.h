#pragma once

#include "HRingProgressBar.h"
#include "HAnimationProgress_p.h"

HE_BEGIN_NAMESPACE

class HRingProgressBarPrivate : public HAnimationProgressPrivate
{
public:
    bool reverse = false;
    bool showPercent = false;
    int alarmMode = 0;
    int angleStart = 90;
    int ringPadding = 3;
    int ringWidth = 15;
    int ringValue1 = 10;
    int ringValue2 = 30;
    int ringValue3 = 70;
    QColor background = QColor(250, 250, 250);
    QColor textColor = QColor(50, 50, 50);
    QColor circleColor = QColor(240, 240, 240);
    QColor ringBackground = QColor(250, 250, 250);
    QColor ringColor = QColor(23, 160, 134);
    QColor ringColor1 = QColor(24, 189, 155);
    QColor ringColor2 = QColor(255, 192, 0);
    QColor ringColor3 = QColor(255, 107, 107);
};

HE_END_NAMESPACE
