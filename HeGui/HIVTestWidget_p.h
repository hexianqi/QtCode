#pragma once

#include "HIVTestWidget.h"
#include "HTestWidget_p.h"

class HEntireTableWidget;
class HDynamicChartView;

HE_BEGIN_NAMESPACE

class ITextStream;

class HIVTestWidgetPrivate : public HTestWidgetPrivate
{
public:
    HIVTestWidgetPrivate();

public:
    ITextStream *stream = nullptr;
    HEntireTableWidget *tableWidget = nullptr;
    HDynamicChartView *chartView = nullptr;

public:
    QPolygonF data;
};

HE_END_NAMESPACE
