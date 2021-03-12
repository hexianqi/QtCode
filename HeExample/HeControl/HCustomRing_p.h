#pragma once

#include "HCustomRing.h"

HE_CONTROL_BEGIN_NAMESPACE

class HCustomRingPrivate
{
public:
    bool showTitle = true;
    QString title;
    int titleHeight;
    int titleFontSize;
    bool showLegend;
    int legendHeight;
    int legendFontSize;
    QColor background;
    QColor textColor;
    QColor highColor;
    QColor flagColor;
    QColor outerCircleColor;
    QColor innerCircleColor;
    QColor centerCircleColor;
    QString outerPieInfos;
    QString innerPieInfos;
};

HE_CONTROL_END_NAMESPACE
