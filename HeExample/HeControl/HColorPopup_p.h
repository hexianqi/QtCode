#pragma once

#include "HColorPopup.h"

class QPushButton;

HE_BEGIN_NAMESPACE

class HColorPopupPrivate
{
public:
    QListView *view;
    QPushButton *button;
    QColor currentColor;
};

HE_END_NAMESPACE
