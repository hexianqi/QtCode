#pragma once

#include "HSpecTestWidget.h"
#include "HTestWidget_p.h"

class HCie1931Widget;
class HTm30SpdChartView;
class HTm30CvgWidget;
class HTm30GamutWidget;
class HTm30RfRgChartView;
class HTm30RfiChartView;
class HTm30RfhjChartView;
class HTm30RcshjChartView;
class HTm30RhshjChartView;

HE_BEGIN_NAMESPACE

class IConfigManage;
class ITestResult;
class ISqlHandle;
class IPrint;
class IPrintTemplate;
class ITextExport;
class ITextExportTemplate;
class HSpecEnergyWidget;
class HSpecChromatismChartView;
class HResultTableWidget;
class ITestDetailWidget;

class HSpecTestWidgetPrivate : public HTestWidgetPrivate
{
public:
    HSpecTestWidgetPrivate();

public:
    HCie1931Widget *cieWidget = nullptr;
    HCie1931Widget *cieWidget2 = nullptr;
    HTm30SpdChartView *spdWidget = nullptr;
    HTm30CvgWidget *cvgWidget = nullptr;
    HTm30GamutWidget *gamutWidget = nullptr;
    HTm30RfRgChartView *rfrgWidget = nullptr;
    HTm30RfiChartView *rfiWidget = nullptr;
    HTm30RfhjChartView *rfhjWidget = nullptr;
    HTm30RcshjChartView *rcshjWidget = nullptr;
    HTm30RhshjChartView *rhshjWidget = nullptr;
    QDialog *cieDialog = nullptr;
    HSpecEnergyWidget *energyWidget = nullptr;
    HSpecChromatismChartView *chromatismWidget = nullptr;
    HResultTableWidget *tableWidget = nullptr;
    ITestDetailWidget *detailWidget = nullptr;

public:
    QAction *actionPrintPreview = nullptr;
    QAction *actionPrintTag = nullptr;
    QAction *actionExportDatabaseLast = nullptr;
    QAction *actionExportDatabase = nullptr;
    QAction *actionExportPath = nullptr;
    QAction *actionSyncFile = nullptr;
    QAction *actionRemove = nullptr;
    QAction *actionAdjust = nullptr;
    QAction *actionProductEidt = nullptr;

public:
    IConfigManage *configManage = nullptr;
    ITestResult *testResult = nullptr;
    ISqlHandle *sqlHandle = nullptr;
    IPrint *print = nullptr;
    IPrintTemplate *specPrintTemplate = nullptr;
    IPrintTemplate *tagPrintTemplate = nullptr;
    ITextExport *textExport = nullptr;
    ITextExportTemplate *specTextTemplate = nullptr;

public:
    QTimer *timer = nullptr;
    bool productEditable = true;
    QStringList displays;
    QStringList tableSelecteds;
    QString exportPath;
    QString syncFile;
    int syncInterval = 20;
};

HE_END_NAMESPACE

