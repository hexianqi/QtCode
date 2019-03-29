#ifndef HSPECFITTINGWIDGET_P_H
#define HSPECFITTINGWIDGET_P_H

#include "HSpecFittingWidget.h"
#include "HeController/HControllerGlobal.h"

HE_CONTROLLER_BEGIN_NAMESPACE
class IModel;
class ITestSpec;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

class QProgressDialog;

HE_GUI_BEGIN_NAMESPACE

class HSpecFittingWidgetPrivate
{
public:
    HSpecFittingWidgetPrivate(HSpecFitting *);

public:
    IModel *model;
    ITestSpec *testSpec;
    HSpecFitting *data;
    QProgressDialog *progressDialog;

public:
    bool testState = false;
    int pel;
    int curTimes;
    QPolygonF points;
};

HE_GUI_END_NAMESPACE

#endif // HSPECFITTINGWIDGET_P_H
