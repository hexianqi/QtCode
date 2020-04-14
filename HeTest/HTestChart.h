#ifndef HTESTCHART_H
#define HTESTCHART_H

#include <QtCore/QPointF>
#include <QtGui/QPolygonF>
#include <QtCharts/QChartGlobal>

QT_CHARTS_BEGIN_NAMESPACE
class QChartView;
QT_CHARTS_END_NAMESPACE
QT_CHARTS_USE_NAMESPACE

class HTestChart
{
public:
    static QChartView *zoomChart();
    static QChartView *lineChart(QList<QPolygonF> polys);
    static QChartView *diffChart(const QPolygonF &p1, const QPolygonF &p2);
    static QChartView *vernierChart(const QPolygonF &p1, const QPolygonF &p2);
};

#endif // HTESTCHART_H
