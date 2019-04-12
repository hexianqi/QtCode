#include "HChart_p.h"

HChart::HChart(QGraphicsItem *parent, Qt::WindowFlags wFlags) :
    QChart(parent, wFlags),
    d_ptr(new HChartPrivate)
{
}

HChart::HChart(HChartPrivate &p, QGraphicsItem *parent, Qt::WindowFlags wFlags) :
    QChart(parent, wFlags),
    d_ptr(&p)
{
}

HChart::~HChart()
{
}
