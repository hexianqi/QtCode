#ifndef HTESTWIDGET2000_P_H
#define HTESTWIDGET2000_P_H

#include "HTestWidget2000.h"
#include "HeGui/HTestWidget_p.h"

class HCIE1931Widget;

HE_DATA_BEGIN_NAMESPACE
class IConfigManage;
HE_DATA_END_NAMESPACE

HE_GUI_BEGIN_NAMESPACE
class HSpecEnergyWidget;
class HResultTableWidget;
class ITestSetWidget;
class ITestDetailWidget;
HE_GUI_END_NAMESPACE

class HTestWidget2000Private : public HTestWidgetPrivate
{
public:
    HTestWidget2000Private();

public:
    IConfigManage *configManage;
    HSpecEnergyWidget *energyWidget;
    HCIE1931Widget *cieWidget;
    HResultTableWidget *resultWidget;
    ITestSetWidget *testSetWidget;
    ITestDetailWidget *detailWidget;

public:
    QAction *actionClear;
    QAction *actionAdjust;

public:
    bool useAdjust = false;
};

#endif // HTESTWIDGET2000_P_H
