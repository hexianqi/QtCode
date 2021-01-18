#ifndef HABSTRACTTESTWIDGET_P_H
#define HABSTRACTTESTWIDGET_P_H

#include "HAbstractTestWidget.h"
#include "HeController/HControllerGlobal.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class ITestData;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE
class IModel;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class ITestSetWidget;

class HE_GUI_EXPORT HAbstractTestWidgetPrivate
{
public:
    HAbstractTestWidgetPrivate();

public:
    ITestSetWidget *testSetWidget = nullptr;
    IModel *model;
    ITestData *testData;
    QList<QMenu *> menus;
    QList<QToolBar *> toolBars;
};

HE_GUI_END_NAMESPACE


#endif // HABSTRACTTESTWIDGET_P_H
