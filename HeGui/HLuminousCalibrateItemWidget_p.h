#pragma once

#include "HLuminousCalibrateItemWidget.h"

HE_GUI_BEGIN_NAMESPACE

class HLuminousCalibrateItemWidgetPrivate
{
public:
    ILuminousCalibrateItem *data = nullptr;
    QString type;
    QStringList types;
    int column = 0;
};

HE_GUI_END_NAMESPACE
