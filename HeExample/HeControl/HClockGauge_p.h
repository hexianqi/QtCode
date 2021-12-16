#pragma once

#include "HClockGauge.h"

class QPropertyAnimation;

HE_BEGIN_NAMESPACE

class HClockGaugePrivate
{
public:
    QColor foreground = QColor(255, 255, 255);
    QColor background = QColor(65, 65, 65);
    QColor crownColorStart = QColor(255, 255, 255);
    QColor crownColorEnd = QColor(166, 166, 166);
    QColor pointerHourColor = QColor(160, 160, 160);
    QColor pointerMinColor = QColor(160, 160, 160);
    QColor pointerSecColor = QColor(160, 160, 160);
    HClockGauge::SecondStyle secondStyle = HClockGauge::SecondStyle_Normal;

public:
    int hour;
    int min;
    int sec;
    double angleSpring = 0;
    QTimer *timer = nullptr;
    QPropertyAnimation *animation = nullptr;
};

HE_END_NAMESPACE
