#pragma once

#include "HDefenceButton.h"

HE_BEGIN_NAMESPACE

class IEventFilter;

class HDefenceButtonPrivate
{
public:
    HDefenceButton::ButtonStyle buttonStyle   = HDefenceButton::ButtonStyle_Police;
    HDefenceButton::ButtonStatus buttonStatus = HDefenceButton::ButtonStatus_Arming;
    QString text = "1";
    bool moveEnable = true;
    bool isDark = false;
    QString type;
    QString imageName;
    IEventFilter *filter = nullptr;
    QTimer *timer = nullptr;
};

HE_END_NAMESPACE
