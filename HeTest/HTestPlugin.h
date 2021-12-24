#pragma once

#include <QtCore/QPointF>
#include <QtGui/QPolygonF>
#include <QtCharts/QChartView>

QT_CHARTS_USE_NAMESPACE

class HTestPlugin
{
public:
    static QChartView *testCIE1931View();
    static QChartView *zoomChart();
    static QChartView *lineChart(QList<QPolygonF> polys);
    static QChartView *diffChart(const QPolygonF &p1, const QPolygonF &p2);
    static QChartView *vernierChart(const QPolygonF &p1, const QPolygonF &p2);
};

