#pragma once

#include "HColorButton.h"

HE_CONTROL_BEGIN_NAMESPACE

class HColorModel;
class HColorPopup;

class HColorButtonPrivate
{
public:
    bool dragEnabled = false;
    bool showName = true;
    QString currentName;
    QColor currentColor;
    QPoint pressPos;
    HColorModel *model = nullptr;
    HColorPopup *popup = nullptr;
};

HE_CONTROL_END_NAMESPACE
