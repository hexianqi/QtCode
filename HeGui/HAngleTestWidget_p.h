#pragma once

#include "HAngleTestWidget.h"
#include "HTestWidget_p.h"

class HDynamicChartView;
class HPolarChartView;

HE_BEGIN_NAMESPACE

class ITestDetailWidget;
class ISqlHandle;
class ITextExport;
class ITextExportTemplate;

class HAngleTestWidgetPrivate : public HTestWidgetPrivate
{
public:
    HAngleTestWidgetPrivate();

public:
    ITestDetailWidget *detailWidget = nullptr;
    HDynamicChartView *cartesianChartView = nullptr;
    HPolarChartView *polarChartView = nullptr;

public:
    QAction *actionExportDatabase = nullptr;

public:
    ISqlHandle *sqlHandle = nullptr;
    ITextExport *textExport = nullptr;
    ITextExportTemplate *textExportTemplate = nullptr;
};

HE_END_NAMESPACE

