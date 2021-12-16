#pragma once

#include "HAdjust2EditWidget.h"
#include <QModelIndex>

class QStringListModel;

HE_BEGIN_NAMESPACE

class IDataFactory;
class ITestData;
class IAdjustItemCollection;
class IModel;
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

HE_END_NAMESPACE
