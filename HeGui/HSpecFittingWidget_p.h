#pragma once

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
    IModel *model = nullptr;
    ITestSpec *testSpec = nullptr;
    HSpecFitting *data = nullptr;
    QProgressDialog *progressDialog = nullptr;

public:
    bool testState = false;
    int pel = 0;
    int curTimes = 0;
    double lastSample = 0.0;
    QPointF integralTime;
    QPolygonF points;
};

HE_GUI_END_NAMESPACE
