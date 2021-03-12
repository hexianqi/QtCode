#pragma once

#include "HCompassGauge.h"

class QPropertyAnimation;

HE_CONTROL_BEGIN_NAMESPACE

class HCompassGaugePrivate
{
public:
    double value = 0;
    int decimal = 0;
    QColor foreground = QColor(255, 255, 255);
    QColor backgroundStart = QColor(81, 97, 113);
    QColor backgroundEnd = QColor(28, 34, 40);
    QColor textColor = QColor(20, 20, 20);
    QColor darkColor = QColor(51, 60, 75);
    QColor lightColor = QColor(109, 134, 162);
    QColor northPointerColor = QColor(255, 107, 107);
    QColor southPointerColor = QColor(100, 184, 255);
    QColor crownColorStart = QColor(125, 32, 36);
    QColor crownColorEnd = QColor(227, 77, 77);
    QColor centerColorStart = QColor(230, 230, 230);
    QColor centerColorEnd = QColor(210, 210, 210);
    double currentValue = 0;
    QPropertyAnimation *animation = nullptr;
};

HE_CONTROL_END_NAMESPACE
