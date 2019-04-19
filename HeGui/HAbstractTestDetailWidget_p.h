#ifndef HABSTRACTTESTDETAILWIDGET_P_H
#define HABSTRACTTESTDETAILWIDGET_P_H

#include "HAbstractTestDetailWidget.h"
#include "HeController/HControllerGlobal.h"

HE_CONTROLLER_BEGIN_NAMESPACE
class ITestData;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HE_GUI_EXPORT HAbstractTestDetailWidgetPrivate
{
public:
    HAbstractTestDetailWidgetPrivate();

public:
    ITestData *testData;
};

HE_GUI_END_NAMESPACE

#endif // HABSTRACTTESTDETAILWIDGET_P_H
