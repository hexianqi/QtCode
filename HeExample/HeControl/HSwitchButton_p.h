#ifndef HSWITCHBUTTON_P_H
#define HSWITCHBUTTON_P_H

#include "HSwitchButton.h"

HE_CONTROL_BEGIN_NAMESPACE

class HSwitchButtonPrivate
{
public:
    int space;
    int rectRadius;
    bool checked;
    bool showText;
    bool showCircle;
    bool animation;
    HSwitchButton::ButtonStyle buttonStyle;
    QColor backgroundOff;
    QColor backgroundOn;
    QColor sliderColorOff;
    QColor sliderColorOn;
    QColor textColorOff;
    QColor textColorOn;
    QString textOff;
    QString textOn;
};

HE_CONTROL_END_NAMESPACE

#endif // HSWITCHBUTTON_P_H
