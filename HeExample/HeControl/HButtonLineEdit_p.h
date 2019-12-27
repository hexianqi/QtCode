#ifndef HBUTTONLINEEDIT_P_H
#define HBUTTONLINEEDIT_P_H

#include "HButtonLineEdit.h"

HE_CONTROL_BEGIN_NAMESPACE

class HButtonLineEditPrivate
{
public:
    QToolButton *button = nullptr;
    HButtonLineEdit::Position position = HButtonLineEdit::Position_RightInside;
    bool visible = true;
};

HE_CONTROL_END_NAMESPACE

#endif // HBUTTONLINEEDIT_P_H
