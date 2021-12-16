#pragma once

#include "HTimeTooltip.h"

HE_BEGIN_NAMESPACE

class HTimeTooltipPrivate
{
public:
    QPoint pos;
    QString time;
    QString text;
    QString displayedText;
    QFont font;
    QRect box;
    QPainterPath path;
    int tipX;
    int tipHeight = 5;
};

HE_END_NAMESPACE

