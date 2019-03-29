#ifndef HABSTRACTDETAILWIDGET_P_H
#define HABSTRACTDETAILWIDGET_P_H

#include "HAbstractDetailWidget.h"
#include "HeController/HControllerGlobal.h"

HE_CONTROLLER_BEGIN_NAMESPACE
class ITestData;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HE_GUI_EXPORT HAbstractDetailWidgetPrivate
{
public:
    HAbstractDetailWidgetPrivate();

public:
    ITestData *testData;
};

HE_GUI_END_NAMESPACE

#endif // HABSTRACTDETAILWIDGET_P_H
