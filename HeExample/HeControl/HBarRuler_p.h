#pragma once

#include "HBarRuler.h"
#include "HAbstractProgress_p.h"

HE_BEGIN_NAMESPACE

class HBarRulerPrivate : public HAbstractProgressPrivate
{
public:
    int longStep = 10;
    int shortStep = 1;
    int space = 20;
    bool animation = false;
    double animationStep = 0.5;
    QColor backgroundStart = QColor(100, 100, 100);
    QColor backgroundEnd = QColor(60, 60, 60);
    QColor lineColor = QColor(255, 255, 255);
    QColor barBackground = QColor(220, 220, 220);
    QColor barColor = QColor(0, 255, 255);
    bool reverse = false;
    double currentValue = 20;
    QTimer *timer = nullptr;
};

HE_END_NAMESPACE
