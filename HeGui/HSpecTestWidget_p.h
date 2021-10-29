#pragma once

#include "HSpecTestWidget.h"
#include "HTestWidget_p.h"

class HCie1931Widget;

HE_DATA_BEGIN_NAMESPACE
class IConfigManage;
class IPrint;
class IPrintTemplate;
HE_DATA_END_NAMESPACE

HE_CONTROLLER_BEGIN_NAMESPACE
class IMemento;
HE_CONTROLLER_END_NAMESPACE

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
    QAction *actionPrintPreviewLast = nullptr;
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
    IPrint *print = nullptr;
    IPrintTemplate *specPrintTemplate = nullptr;
    ITestResult *testResult = nullptr;

public:
    QTimer *timer = nullptr;
    bool modified = true;
    bool productEditable = false;
    QStringList displays;
    QStringList tableSelecteds;
    QString exportPathName;
    QString syncFileName;
    int syncInterval = 20;
};

HE_GUI_END_NAMESPACE

