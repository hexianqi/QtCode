#ifndef HSPECCALIBRATESETWIDGET_P_H
#define HSPECCALIBRATESETWIDGET_P_H

#include "HSpecCalibrateSetWidget.h"
#include "HAbstractTestSetWidget_p.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class ITestSpec;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HSpecCalibrateSetWidgetPrivate : public HAbstractTestSetWidgetPrivate
{
public:
    HSpecCalibrateSetWidgetPrivate();

public:
    ITestSpec *testSpec;
    bool integralTimeAuto = false;
};

HE_GUI_END_NAMESPACE

#endif // HSPECCALIBRATESETWIDGET_P_H
