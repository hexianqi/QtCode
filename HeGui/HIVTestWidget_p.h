#ifndef HIVTESTWIDGET_P_H
#define HIVTESTWIDGET_P_H

#include "HIVTestWidget.h"
#include "HTestWidget_p.h"

class HEntireTableWidget;
class HDynamicChartView;

HE_GUI_BEGIN_NAMESPACE

class HIVTestWidgetPrivate : public HTestWidgetPrivate
{
public:
    HIVTestWidgetPrivate();

public:
    HEntireTableWidget *tableWidget;
    HDynamicChartView *chartView;

public:
    QPolygonF data;
};

HE_GUI_END_NAMESPACE

#endif // HIVTESTWIDGET_P_H
