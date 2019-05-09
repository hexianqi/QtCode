#ifndef HSPECFITTINGWIDGET_P_H
#define HSPECFITTINGWIDGET_P_H

#include "HSpecFittingWidget.h"
#include "HeController/HControllerGlobal.h"

class QProgressDialog;

HE_DATA_BEGIN_NAMESPACE
class ITestSpec;
HE_DATA_END_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE
class IModel;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HSpecFittingWidgetPrivate
{
public:
    HSpecFittingWidgetPrivate();

public:
    IModel *model;
    ITestSpec *testSpec;
    HSpecFitting *data;
    QProgressDialog *progressDialog;

public:
    bool testState = false;
    int pel;
    int curTimes;
    double lastSample;
    QPolygonF points;
};

HE_GUI_END_NAMESPACE

#endif // HSPECFITTINGWIDGET_P_H
