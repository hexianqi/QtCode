#ifndef HRESULTTABLEWIDGET_P_H
#define HRESULTTABLEWIDGET_P_H

#include "HResultTableWidget.h"
#include "HeController/HControllerGlobal.h"
#include "HePlugin/HEntireTableWidget_p.h"

HE_CONTROLLER_BEGIN_NAMESPACE
class ITestData;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HResultTableWidgetPrivate : public HEntireTableWidgetPrivate
{
public:
    HResultTableWidgetPrivate();

public:
    ITestData *testData;
    QStringList optionals;
    QStringList selecteds;

public:
    QAction *actionClear;
    QAction *actionOptional;
};

HE_GUI_END_NAMESPACE

#endif // HRESULTTABLEWIDGET_P_H
