#ifndef HELECCALIBRATEITEMWIDGET_P_H
#define HELECCALIBRATEITEMWIDGET_P_H

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

#endif // HELECCALIBRATEITEMWIDGET_P_H
