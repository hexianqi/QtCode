#ifndef HABSTRACTTESTSETWIDGET_P_H
#define HABSTRACTTESTSETWIDGET_P_H

#include "HAbstractTestSetWidget.h"
#include "HeController/HControllerGlobal.h"

HE_CONTROLLER_BEGIN_NAMESPACE
class IModel;
class ITestData;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HE_GUI_EXPORT HAbstractTestSetWidgetPrivate
{
public:
    HAbstractTestSetWidgetPrivate();

public:
    IModel *model;
    ITestData *testData;
    bool testState = false;
    int testMode = 0;
};

HE_GUI_END_NAMESPACE


#endif // HABSTRACTTESTSETWIDGET_P_H
