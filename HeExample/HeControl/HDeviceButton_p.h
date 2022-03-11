#pragma once

#include "HDeviceButton.h"

HE_BEGIN_NAMESPACE

class IEventFilter;

class HDeviceButtonPrivate
{
public:
    HDeviceButton::ButtonStyle buttonStyle = HDeviceButton::ButtonStyle_Police;
    HDeviceButton::ButtonColor buttonColor = HDeviceButton::ButtonColor_Green;
    QString text = "1";
    bool moveEnable = true;
    bool isDark = false;
    QString type;
    QString imageName;
    IEventFilter *filter = nullptr;
    QTimer *timer = nullptr;
};

HE_END_NAMESPACE
