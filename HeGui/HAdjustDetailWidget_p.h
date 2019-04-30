#ifndef HADJUSTDETAILWIDGET_P_H
#define HADJUSTDETAILWIDGET_P_H

#include "HAdjustDetailWidget.h"

class HEntireTableWidget;

HE_DATA_BEGIN_NAMESPACE
class IDataFactory;
class IAdjust;
HE_DATA_END_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HAdjustDetailWidgetPrivate
{
public:
    HAdjustDetailWidgetPrivate();

public:
    IDataFactory *factory = nullptr;
    IAdjustCollection *adjusts = nullptr;
    IAdjust *adjust = nullptr;
    HEntireTableWidget *tableWidget = nullptr;
};

HE_GUI_END_NAMESPACE

#endif // HADJUSTDETAILWIDGET_P_H
