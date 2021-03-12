#pragma once

#include "HIVTestWidget.h"
#include "HTestWidget_p.h"

class HEntireTableWidget;
class HDynamicChartView;

HE_DATA_BEGIN_NAMESPACE
class ITextStream;
HE_DATA_END_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HIVTestWidgetPrivate : public HTestWidgetPrivate
{
public:
    HIVTestWidgetPrivate();

public:
    ITextStream *stream = nullptr;
    HEntireTableWidget *tableWidget;
    HDynamicChartView *chartView;

public:
    QPolygonF data;
};

HE_GUI_END_NAMESPACE
