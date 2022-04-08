#pragma once

#include "HAngleTestWidget.h"
#include "HTestWidget_p.h"

class HDynamicChartView;

HE_BEGIN_NAMESPACE

class ITestDetailWidget;

class HAngleTestWidgetPrivate : public HTestWidgetPrivate
{
public:
    ITestDetailWidget *detailWidget = nullptr;
    HDynamicChartView *chartView = nullptr;

public:
    QAction *actionExportDatabase = nullptr;

};

HE_END_NAMESPACE

