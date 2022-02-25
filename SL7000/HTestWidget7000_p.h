#pragma once

#include "HTestWidget7000.h"
#include "HeGui\HTestWidget_p.h"

class HCie1931Widget;
class HLocationWidget;
class HTestResult7000;

HE_BEGIN_NAMESPACE
class IConfigManage;
class HSpecEnergyWidget;
class HSpecChromatismChartView;
class HResultTableWidget;
class ITestDetailWidget;
class ITextExport;
class ITextExportTemplate;
HE_END_NAMESPACE

class HTestWidget7000Private : public HTestWidgetPrivate
{
public:
    HTestWidget7000Private();

public:
    HCie1931Widget *cieWidget = nullptr;
    HSpecEnergyWidget *energyWidget = nullptr;
    HSpecChromatismChartView *chromatismWidget = nullptr;
    HResultTableWidget *tableWidget = nullptr;
    HLocationWidget *locationWidget = nullptr;
    ITestDetailWidget *detailWidget = nullptr;

public:
    QAction *actionExportPath = nullptr;
    QAction *actionAdjust = nullptr;
    QAction *actionProbe = nullptr;
    QAction *actionProductEidt = nullptr;

public:
    IConfigManage *configManage = nullptr;
    HTestResult7000 *testResult = nullptr;
    ITextExport *textExport = nullptr;
    ITextExportTemplate *textTemplate = nullptr;
    QPolygon polygon;

public:
    QStringList displays;
    QStringList tableSelecteds;
    QString exportPath;
};

