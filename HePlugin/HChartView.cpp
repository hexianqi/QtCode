#include "HChartView_p.h"

HChartView::HChartView(QWidget *parent) :
    QChartView(parent),
    d_ptr(new HChartViewPrivate)
{
}

HChartView::HChartView(QChart *chart, QWidget *parent) :
    QChartView(chart, parent),
    d_ptr(new HChartViewPrivate)
{
}

HChartView::HChartView(HChartViewPrivate &p, QChart *chart, QWidget *parent) :
    QChartView(chart, parent),
    d_ptr(&p)
{
}

HChartView::~HChartView()
{
}
