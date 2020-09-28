#ifndef HADJUSTEDITWIDGET_P_H
#define HADJUSTEDITWIDGET_P_H

#include "HAdjustEditWidget.h"
#include "HeController/HControllerGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class IDataFactory;
class ITestData;
HE_DATA_END_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE
class IModel;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HSpecEnergyWidget;
class ITestSetWidget;

class HAdjustEditWidgetPrivate
{
public:
    HAdjustEditWidgetPrivate();

public:
    IDataFactory *factory = nullptr;
    IAdjust *data = nullptr;
    QStringList optionals;
    QStringList selecteds;
    QStringList unselecteds;

public:
    IModel *model = nullptr;
    ITestData *testData = nullptr;
    HSpecEnergyWidget *energyWidget = nullptr;
    ITestSetWidget *testSetWidget = nullptr;
};

HE_GUI_END_NAMESPACE

#endif // HADJUSTEDITWIDGET_P_H
