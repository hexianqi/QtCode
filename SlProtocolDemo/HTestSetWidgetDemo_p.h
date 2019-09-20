#ifndef HTESTSETWIDGETDEMO_P_H
#define HTESTSETWIDGETDEMO_P_H

#include "HTestSetWidgetDemo.h"
#include "HeGui/HAbstractTestSetWidget_p.h"

HE_DATA_BEGIN_NAMESPACE
class ITestSpec;
HE_DATA_END_NAMESPACE

class HTestSetWidgetDemoPrivate : public HAbstractTestSetWidgetPrivate
{
public:
    HTestSetWidgetDemoPrivate();

public:
    ITestSpec *testSpec;
    bool integralTimeAuto = false;
    bool energy = false;
};

#endif // HTESTSETWIDGETDEMO_P_H
