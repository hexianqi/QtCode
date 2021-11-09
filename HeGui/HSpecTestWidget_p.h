#pragma once

#include "HSpecTestWidget.h"
#include "HTestWidget_p.h"
#include "HeSql/HSqlGlobal.h"

class HCie1931Widget;

HE_DATA_BEGIN_NAMESPACE
class IConfigManage;
class IPrint;
class IPrintTemplate;
class ITextExport;
class ITextExportTemplate;
HE_DATA_END_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE
class IMemento;
HE_CONTROLLER_END_NAMESPACE

HE_SQL_BEGIN_NAMESPACE
class ISqlHandle;
HE_SQL_END_NAMESPACE
HE_SQL_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HSpecEnergyWidget;
class HSpecChromatismChartView;
class HResultTableWidget;
class ITestDetailWidget;
class ITestResult;

class HE_GUI_EXPORT HSpecTestWidgetPrivate : public HTestWidgetPrivate
{
public:
    HSpecTestWidgetPrivate();

public:
    HSpecEnergyWidget *energyWidget = nullptr;
    HSpecChromatismChartView *chromatismWidget = nullptr;
    HCie1931Widget *cieWidget = nullptr;
    HCie1931Widget *cieWidget2 = nullptr;
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
    bool modified = true;
    bool productEditable = false;
    QStringList displays;
    QStringList tableSelecteds;
    QString exportPath;
    QString syncFile;
    int syncInterval = 20;
};

HE_GUI_END_NAMESPACE

