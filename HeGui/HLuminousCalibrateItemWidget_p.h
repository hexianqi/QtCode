#pragma once

#include "HLuminousCalibrateItemWidget.h"

HE_BEGIN_NAMESPACE

class HLuminousCalibrateItemWidgetPrivate
{
public:
    ILuminousCalibrateItem *data = nullptr;
    QString type;
    QStringList types;
    int column = 0;
};

HE_END_NAMESPACE
