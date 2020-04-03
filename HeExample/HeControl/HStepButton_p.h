#ifndef HSTEPBUTTTON_P_H
#define HSTEPBUTTTON_P_H

#include "HStepButton.h"

class QHBoxLayout;
class QPushButton;

HE_CONTROL_BEGIN_NAMESPACE

class HStepButtonPrivate
{
public:
    QHBoxLayout *layout;
    QList<QPushButton *> buttons;
    QString qss;
};

HE_CONTROL_END_NAMESPACE

#endif // HSTEPBUTTTON_P_H
