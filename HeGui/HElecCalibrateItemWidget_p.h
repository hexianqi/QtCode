#pragma once

#include "HElecCalibrateItemWidget.h"

HE_BEGIN_NAMESPACE

class HElecCalibrateItemWidgetPrivate
{
public:
    IElecCalibrateItem *data = nullptr;
    HElecType type;
    int gears;
};

HE_END_NAMESPACE
