#pragma once

#include "HButtonLineEdit.h"

HE_BEGIN_NAMESPACE

class HButtonLineEditPrivate
{
public:
    QToolButton *button = nullptr;
    HButtonLineEdit::Position position = HButtonLineEdit::Position_RightInside;
    bool visible = true;
};

HE_END_NAMESPACE
