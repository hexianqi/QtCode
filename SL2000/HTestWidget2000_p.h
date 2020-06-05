#ifndef HTESTWIDGET2000_P_H
#define HTESTWIDGET2000_P_H

#include "HTestWidget2000.h"
#include "HeGui/HTestWidget2_p.h"

class HCie1931Widget;

HE_DATA_BEGIN_NAMESPACE
class IConfigManage;
HE_DATA_END_NAMESPACE

HE_GUI_BEGIN_NAMESPACE
class HSpecEnergyWidget;
class HSpecChromatismChartView;
class HResultTableWidget;
class ITestSetWidget;
class ITestDetailWidget;
HE_GUI_END_NAMESPACE

class HTestWidget2000Private : public HTestWidget2Private
{
public:
    HTestWidget2000Private();

public:
    IConfigManage *configManage = nullptr;
    HSpecEnergyWidget *energyWidget = nullptr;
    HSpecChromatismChartView *chromatismWidget = nullptr;
    HCie1931Widget *cieWidget = nullptr;
    HResultTableWidget *resultWidget = nullptr;
    ITestSetWidget *testSetWidget = nullptr;
    ITestDetailWidget *detailWidget = nullptr;

public:
    QAction *actionAdjust = nullptr;
    QAction *actionSetRam = nullptr;
    QAction *actionGetRam = nullptr;
    QAction *actionImportCurve = nullptr;
    QAction *actionExportCurve = nullptr;

public:
    bool modified = true;
};

#endif // HTESTWIDGET2000_P_H
