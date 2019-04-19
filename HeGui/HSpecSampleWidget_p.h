#ifndef HSPECSAMPLEWIDGET_P_H
#define HSPECSAMPLEWIDGET_P_H

#include "HSpecSampleWidget.h"
#include "HeController/HControllerGlobal.h"
#include "HePlugin/HVernierWidget_p.h"

HE_CONTROLLER_BEGIN_NAMESPACE
class ITestSpec;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HSpecSampleWidgetPrivate : public HVernierWidgetPrivate
{
public:
    HSpecSampleWidgetPrivate(HSpecSampleWidget *);

public:
    ITestSpec *testSpec;

public:
    QAction *actionCurve1;
    QAction *actionCurve2;

public:
    bool enablePeak = true;
    QList<bool> curveVisibles;
    QList<double> verniers;
};

HE_GUI_END_NAMESPACE

#endif // HSPECSAMPLEWIDGET_P_H
