#pragma once

#include "HAdjustEditWidget.h"

HE_BEGIN_NAMESPACE

class IDataFactory;
class ITestData;
class IModel;
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

HE_END_NAMESPACE
