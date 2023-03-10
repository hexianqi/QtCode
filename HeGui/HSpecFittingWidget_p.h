#pragma once

#include "HSpecFittingWidget.h"

class QProgressDialog;

HE_BEGIN_NAMESPACE

class ITestSpec;
class IModel;

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
    int polyTime = 7;
    int pel = 0;
    int curTimes = 0;
    QPointF integralTime;
    QPolygonF points;
};

HE_END_NAMESPACE
