#ifndef HIMAGESWITCH_P_H
#define HIMAGESWITCH_P_H

#include "HImageSwitch.h"

HE_CONTROL_BEGIN_NAMESPACE

class HImageSwitchPrivate
{
public:
    bool checked = false;
    HImageSwitch::ButtonStyle buttonStyle = HImageSwitch::ButtonStyle_1;
    QString imageName;
    QString imageNameOn;
    QString imageNameOff;
};

HE_CONTROL_END_NAMESPACE

#endif // HIMAGESWITCH_P_H
