#pragma once

#include "HLedNumber.h"

HE_CONTROL_BEGIN_NAMESPACE

class HLedNumberPrivate
{
public:
    int number = 3;
    int space = 5;
    int padding = 2;
    int radius = 2;
    QColor backgroundStart = QColor(100, 100, 100);
    QColor backgroundEnd = QColor(60, 60, 60);
    QColor numberBackgroundStart = QColor(130, 130, 130);
    QColor numberBackgroundEnd = QColor(90, 90, 90);
    QColor numberColorStart = QColor(100, 184, 255);
    QColor numberColorEnd = QColor(79, 148, 205);
    QHash<int, QPolygon>  position;
};

HE_CONTROL_END_NAMESPACE
