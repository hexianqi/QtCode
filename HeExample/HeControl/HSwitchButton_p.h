#pragma once

#include "HSwitchButton.h"

class QPropertyAnimation;

HE_BEGIN_NAMESPACE

class HSwitchButtonPrivate
{
public:
    int space = 2;
    int rectRadius = 5;
    bool checked = false;
    bool showText = true;
    bool showCircle = true;
    bool animationEnable = true;
    HSwitchButton::ButtonStyle buttonStyle = HSwitchButton::ButtonStyle_CircleIn;
    QColor backgroundOff = QColor(111, 122, 126);
    QColor backgroundOn = QColor(21, 156, 119);
    QColor sliderColorOff = QColor(255, 255, 255);
    QColor sliderColorOn = QColor(255, 255, 255);
    QColor textColorOff = QColor(250, 250, 250);
    QColor textColorOn = QColor(255, 255, 255);
    QString textOff = "Off";
    QString textOn = "On";

    int pos = 0;
    QPropertyAnimation *animation = nullptr;
};

HE_END_NAMESPACE
