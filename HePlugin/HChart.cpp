#include "HChart_p.h"

HChart::HChart(QGraphicsItem *parent, Qt::WindowFlags wFlags) :
    QChart(parent, wFlags),
    d_ptr(new HChartPrivate)
{
    setMargins(QMargins(1, 1, 1, 1));
}

HChart::HChart(HChartPrivate &p, QGraphicsItem *parent, Qt::WindowFlags wFlags) :
    QChart(parent, wFlags),
    d_ptr(&p)
{
    setMargins(QMargins(1, 1, 1, 1));
}

HChart::~HChart() = default;
