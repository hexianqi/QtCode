#pragma once

#include "HTestWidget1000I.h"
#include "HeGui/HTestWidget_p.h"

HE_BEGIN_NAMESPACE
class IConfigManage;
class ISyncTestResult;
class ISqlHandle;
class IPrint;
class IPrintTemplate;
class ITextExport;
class ITextExportTemplate;
class HSpecEnergyWidget;
class HResultTableWidget;
class ITestDetailWidget;
HE_END_NAMESPACE

class HTestWidget1000IPrivate : public HTestWidgetPrivate
{
public:
    HTestWidget1000IPrivate();

public:
    HSpecEnergyWidget *energyWidget = nullptr;
    HResultTableWidget *tableWidget = nullptr;
    ITestDetailWidget *detailWidget = nullptr;

public:
    IConfigManage *configManage = nullptr;
    ISyncTestResult *testResult = nullptr;
    ISqlHandle *sqlHandle = nullptr;
    IPrint *print = nullptr;
    IPrintTemplate *printTemplate = nullptr;
    ITextExport *textExport = nullptr;
    ITextExportTemplate *textExportTemplate = nullptr;

public:
    QAction *actionPrintPreview = nullptr;
    QAction *actionExportDatabaseLast = nullptr;
    QAction *actionExportDatabase = nullptr;
    QAction *actionExportPath = nullptr;
    QAction *actionSyncFile = nullptr;
    QAction *actionRemove = nullptr;
    QAction *actionAdjust = nullptr;

public:
    QTimer *timer = nullptr;
    QStringList displays;
    QStringList tableSelecteds;
    QString exportPath;
    QString syncFile;
    int syncInterval = 20;
};

