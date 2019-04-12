#ifndef HTESTSETWIDGET2000_P_H
#define HTESTSETWIDGET2000_P_H

#include "HTestSetWidget2000.h"
#include "HeGui/HAbstractTestSetWidget_p.h"

HE_CONTROLLER_BEGIN_NAMESPACE
class ITestSpec;
HE_CONTROLLER_END_NAMESPACE

class HTestSetWidget2000Private : public HAbstractTestSetWidgetPrivate
{
public:
    HTestSetWidget2000Private();

public:
    ITestSpec *testSpec;
    bool integralTimeAuto = false;
};

#endif // HTESTSETWIDGET2000_P_H
