#pragma once

#include "HStepButton.h"

class QHBoxLayout;
class QPushButton;

HE_BEGIN_NAMESPACE

class HStepButtonPrivate
{
public:
    QHBoxLayout *layout;
    QList<QPushButton *> buttons;
    QString qss;
};

HE_END_NAMESPACE
