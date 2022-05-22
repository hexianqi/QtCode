#pragma once

#include "HAngleTestWidget.h"
#include "HTestWidget_p.h"

class HDynamicChartView;

HE_BEGIN_NAMESPACE

class HAngleChartView;
class ITestDetailWidget;
class IGuiFactory;
class IConfigManage;
class ISqlHandle;
class IPrint;
class IPrintTemplate;
class ITextExport;
class ITextExportTemplate;

class HAngleTestWidgetPrivate : public HTestWidgetPrivate
{
public:
    HAngleTestWidgetPrivate();

public:
    ITestDetailWidget *detailWidget = nullptr;
    HDynamicChartView *cartesianChartView = nullptr;
    HAngleChartView *polarChartView = nullptr;

public:
    QAction *actionMotorLocation = nullptr;
    QAction *actionMotorReset = nullptr;
    QAction *actionExportDatabase = nullptr;
    QAction *actionPrintPreview = nullptr;
    QTimer *timer = nullptr;

public:
    IGuiFactory *guiFactory = nullptr;
    IConfigManage *configManage = nullptr;
    ISqlHandle *sqlHandle = nullptr;
    IPrint *print = nullptr;
    IPrintTemplate *printTemplate = nullptr;
    ITextExport *textExport = nullptr;
    ITextExportTemplate *textExportTemplate = nullptr;
};

HE_END_NAMESPACE

