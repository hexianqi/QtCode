#pragma once

#include "HAdjust2EditWidget.h"
#include "HeController/HControllerGlobal.h"
#include <QModelIndex>

class QStringListModel;

HE_DATA_BEGIN_NAMESPACE
class IDataFactory;
class ITestData;
class IAdjustItemCollection;
HE_DATA_END_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE
class IModel;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HSpecEnergyWidget;
class ITestSetWidget;

class HAdjust2EditWidgetPrivate
{
public:
    HAdjust2EditWidgetPrivate();

public:
    IDataFactory *factory = nullptr;
    IAdjust2 *data = nullptr;
    IAdjustItemCollection *itemCollection = nullptr;
    QStringListModel *listModel;
    QModelIndex currentIndex;
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
