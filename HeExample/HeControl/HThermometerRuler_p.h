#pragma once

#include "HThermometerRuler.h"
#include "HAnimationProgress_p.h"

HE_CONTROL_BEGIN_NAMESPACE

class HThermometerRulerPrivate : public HAnimationProgressPrivate
{
public:
    int longStep = 10;
    int shortStep = 2;
    int space = 10;
    bool showUserValue = true;
    double userValue = 80.0;
    QColor userValueColor = QColor(255, 107, 107);
    QColor backgroundStart = QColor(100, 100, 100);
    QColor backgroundEnd = QColor(60, 60, 60);
    QColor lineColor = QColor(255, 255, 255);
    QColor barBackground = QColor(230, 230, 230);
    QColor barColor = QColor(100, 184, 255);
    int barWidth;                   // 水银柱宽度
    int barHeight;                  // 水银柱高度
    int radius;                     // 水银柱底部圆半径
    int targetX;                    // 目标X坐标
    QRectF barRect;                 // 柱状区域
    QRectF circleRect;              // 底部圆区域
    HThermometerRuler::BarPosition barPosition = HThermometerRuler::BarPosition_Center;
    HThermometerRuler::TickPosition tickPosition = HThermometerRuler::TickPosition_Both;
};

HE_CONTROL_END_NAMESPACE
