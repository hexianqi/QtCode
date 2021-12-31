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
class IPrint;
class IPrintTemplate;
class ITextExport;
class ITextExportTemplate;
class IMemento;
class ISqlHandle;
class HSpecEnergyWidget;
class HSpecChromatismChartView;
class HResultTableWidget;
class ITestDetailWidget;
class ITestResult;

class HSpecTestWidgetPrivate : public HTestWidgetPrivate
{
public:
    HSpecTestWidgetPrivate();

public:
    HSpecEnergyWidget *energyWidget = nullptr;
    HSpecChromatismChartView *chromatismWidget = nullptr;
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
    QAction *actionQuantum = nullptr;
    QAction *actionProductEidt = nullptr;

public:
    IConfigManage *configManage = nullptr;
    IMemento *memento = nullptr;
    ITestResult *testResult = nullptr;
    ISqlHandle *sqlHandle = nullptr;
    IPrint *print = nullptr;
    IPrintTemplate *specPrintTemplate = nullptr;
    IPrintTemplate *tagPrintTemplate = nullptr;
    ITextExport *textExport = nullptr;
    ITextExportTemplate *specTextTemplate = nullptr;

public:
    QTimer *timer = nullptr;
    bool productEditable = false;
    QStringList displays;
    QStringList tableSelecteds;
    QString exportPath;
    QString syncFile;
    int syncInterval = 20;
};

HE_END_NAMESPACE

