#pragma once

#include "HImageSwitch.h"

HE_BEGIN_NAMESPACE

class HImageSwitchPrivate
{
public:
    bool checked = false;
    HImageSwitch::ButtonStyle buttonStyle = HImageSwitch::ButtonStyle_1;
    QString imageName;
    QString imageNameOn;
    QString imageNameOff;
};

HE_END_NAMESPACE
