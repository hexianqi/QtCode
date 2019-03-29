#ifndef HTESTSETWIDGETSPEC_P_H
#define HTESTSETWIDGETSPEC_P_H

#include "HTestSetWidgetSpec.h"
#include "HeGui/HAbstractTestSetWidget_p.h"
#include "HeController/HControllerGlobal.h"

HE_CONTROLLER_BEGIN_NAMESPACE
class ITestSpec;
HE_CONTROLLER_END_NAMESPACE
HE_CONTROLLER_USE_NAMESPACE

class HTestSetWidgetSpecPrivate : public HAbstractTestSetWidgetPrivate
{
public:
    HTestSetWidgetSpecPrivate();

public:
    ITestSpec *testSpec;
    bool integralTimeAuto = false;
};

#endif // HTESTSETWIDGETSPEC_P_H
