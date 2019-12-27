#ifndef HDEFENCEBUTTON_P_H
#define HDEFENCEBUTTON_P_H

#include "HDefenceButton.h"

HE_CONTROL_BEGIN_NAMESPACE

class IEventFilter;

class HDefenceButtonPrivate
{
public:
    QString text = "1";
    bool moveEnable = true;
    HDefenceButton::ButtonStyle buttonStyle = HDefenceButton::ButtonStyle_Police;
    HDefenceButton::ButtonStatus buttonStatus = HDefenceButton::ButtonStatus_Arming;
    bool isDark = false;
    QString type;
    QString imageName;
    IEventFilter *filter = nullptr;
    QTimer *timer = nullptr;
};

HE_CONTROL_END_NAMESPACE

#endif // HDEFENCEBUTTON_P_H
