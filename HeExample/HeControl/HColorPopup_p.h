#ifndef HCOLORPOPUP_P_H
#define HCOLORPOPUP_P_H

#include "HColorPopup.h"

class QPushButton;

HE_CONTROL_BEGIN_NAMESPACE

class HColorPopupPrivate
{
public:
    QListView *view;
    QPushButton *button;
    QColor currentColor;
};

HE_CONTROL_END_NAMESPACE

#endif // HCOLORPOPUP_P_H
