#pragma once

#include "HGroupButton.h"

class QHBoxLayout;
class QButtonGroup;
class QPushButton;

HE_BEGIN_NAMESPACE

class HGroupButtonPrivate
{
public:
    QHBoxLayout *layout;
    QButtonGroup *buttonGroup;
    QList<QPushButton *> buttons;
};

HE_END_NAMESPACE
