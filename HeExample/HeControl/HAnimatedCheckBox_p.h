#ifndef HANIMATEDCHECKBOX_P_H
#define HANIMATEDCHECKBOX_P_H

#include "HAnimatedCheckBox.h"

class QLabel;
class QPropertyAnimation;

HE_CONTROL_BEGIN_NAMESPACE

class HAnimatedCheckBoxPrivate
{
public:
    QLabel *indicator;
    QPropertyAnimation *animation;
};

HE_CONTROL_END_NAMESPACE

#endif // HANIMATEDCHECKBOX_P_H
