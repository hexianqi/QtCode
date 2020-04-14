/***************************************************************************************************
**      2019-05-21  HChromatismChart 色容差图表。
***************************************************************************************************/

#ifndef HCHROMATISMCHART_H
#define HCHROMATISMCHART_H

#include "HChart.h"

class HChromatismChartPrivate;

class HChromatismChart : public HChart
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HChromatismChart)

public:
    explicit HChromatismChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());

public:
    void setEllipse(const QPolygonF &);
    void setPointFocus(QPointF);
    void setPointCenter(QPointF);
    void setAxesXTitle(const QString &);
    void createFixAxes();

private:
    void init();
};

#endif // HCHROMATISMCHART_H
