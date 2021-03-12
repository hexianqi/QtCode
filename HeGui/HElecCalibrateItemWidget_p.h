#pragma once

#include "HElecCalibrateItemWidget.h"

HE_GUI_BEGIN_NAMESPACE

class HElecCalibrateItemWidgetPrivate
{
public:
    IElecCalibrateItem *data = nullptr;
    HElecType type;
    int gears;
};

HE_GUI_END_NAMESPACE
