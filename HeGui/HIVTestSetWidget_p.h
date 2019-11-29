#ifndef HIVTESTSETWIDGET_P_H
#define HIVTESTSETWIDGET_P_H

#include "HIVTestSetWidget.h"
#include "HAbstractTestSetWidget_p.h"

HE_DATA_BEGIN_NAMESPACE
class ITestElec;
HE_DATA_END_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HIVTestSetWidgetPrivate : public HAbstractTestSetWidgetPrivate
{
public:
    HIVTestSetWidgetPrivate();

public:
    ITestElec *testElec;
    double elecCurrent = 1.0;
    double elecFrom = 1.0;
    double elecTo = 100.0;
    double interval = 1.0;
};

HE_GUI_END_NAMESPACE

#endif // HIVTESTSETWIDGET_P_H
