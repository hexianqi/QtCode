#ifndef HIVTESTWIDGET_P_H
#define HIVTESTWIDGET_P_H

#include "HIVTestWidget.h"
#include "HAbstractTestWidget_p.h"

class HEntireTableWidget;
class HDynamicChartView;

HE_DATA_BEGIN_NAMESPACE
class IExcelStream;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class ITestSetWidget;

class HIVTestWidgetPrivate : public HAbstractTestWidgetPrivate
{
public:
    HIVTestWidgetPrivate();

public:
    IExcelStream *excelStream;
    ITestSetWidget *testSetWidget;
    HEntireTableWidget *tableWidget;
    HDynamicChartView *chartView;

public:
    QAction *actionStart;
    QAction *actionStop;
    QAction *actionExportExcel;
    QAction *actionClear;

public:
    QPolygonF data;
};

HE_GUI_END_NAMESPACE

#endif // HIVTESTWIDGET_P_H
