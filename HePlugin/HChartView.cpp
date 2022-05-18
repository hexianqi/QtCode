#include "HChartView_p.h"

HChartView::HChartView(QWidget *parent) :
    QChartView(parent),
    d_ptr(new HChartViewPrivate)
{
    init();
}

HChartView::HChartView(QChart *chart, QWidget *parent) :
    QChartView(chart, parent),
    d_ptr(new HChartViewPrivate)
{
    init();
}

HChartView::HChartView(HChartViewPrivate &p, QChart *chart, QWidget *parent) :
    QChartView(chart, parent),
    d_ptr(&p)
{
}

void HChartView::init()
{
    setBackgroundBrush(Qt::white);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setContextMenuPolicy(Qt::ActionsContextMenu);
}

HChartView::~HChartView() = default;

