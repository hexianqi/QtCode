#ifndef HGROUPBUTTON_P_H
#define HGROUPBUTTON_P_H

#include "HGroupButton.h"

class QHBoxLayout;
class QButtonGroup;
class QPushButton;

HE_CONTROL_BEGIN_NAMESPACE

class HGroupButtonPrivate
{
public:
    QHBoxLayout *layout;
    QButtonGroup *buttonGroup;
    QList<QPushButton *> buttons;
};

HE_CONTROL_END_NAMESPACE

#endif // HGROUPBUTTON_P_H
