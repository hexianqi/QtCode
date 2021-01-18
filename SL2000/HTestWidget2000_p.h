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
    HCie1931Widget *cieWidget2 = nullptr;
    HResultTableWidget *resultWidget = nullptr;
    ITestDetailWidget *detailWidget = nullptr;
    QDialog *cieDialog = nullptr;

public:
    QAction *actionRemove = nullptr;
    QAction *actionExportDatabase2 = nullptr;
    QAction *actionAdjust = nullptr;
    QAction *actionSetRam = nullptr;
    QAction *actionGetRam = nullptr;
    QAction *actionImportCurve = nullptr;
    QAction *actionExportCurve = nullptr;

public:
    bool modified = true;
};

#endif // HTESTWIDGET2000_P_H
