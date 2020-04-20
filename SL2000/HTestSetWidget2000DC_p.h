#ifndef HTESTSETWIDGET2000DC_P_H
#define HTESTSETWIDGET2000DC_P_H

#include "HTestSetWidget2000DC.h"
#include "HeGui/HAbstractTestSetWidget_p.h"

HE_DATA_BEGIN_NAMESPACE
class ITestSpec;
class ITestElec;
HE_DATA_END_NAMESPACE

class HTestSetWidget2000DCPrivate : public HAbstractTestSetWidgetPrivate
{
public:
    HTestSetWidget2000DCPrivate();

public:
    ITestSpec *testSpec = nullptr;
    ITestElec *testElec = nullptr;
    bool integralTimeAuto = false;
    QTimer *timerContinue = nullptr;
    QTimer *timerInterval = nullptr;
};

#endif // HTESTSETWIDGET2000DC_P_H
