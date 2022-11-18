#pragma once

#include "HLotteryTurntableWidget.h"

HE_BEGIN_NAMESPACE

class HLotteryTurntableWidgetPrivate
{
public:
    QRegion centerRect;
    bool isPressCenter = false;
    bool isRuning = false;
    int rotate = 0;
    QList<Qt::GlobalColor> colors;
};

HE_END_NAMESPACE

