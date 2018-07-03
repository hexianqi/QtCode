/***************************************************************************************************
**      2018-07-03  HMarkerChart 标记可选图表。
***************************************************************************************************/

#ifndef HMARKERCHART_H
#define HMARKERCHART_H

#include <QtUiPlugin/QDesignerExportWidget>
#include <QtCharts/QChart>

QT_CHARTS_USE_NAMESPACE

class HMarkerChartPrivate;

class QDESIGNER_WIDGET_EXPORT HMarkerChart : public QChart
{
    Q_OBJECT

public:
    explicit HMarkerChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = 0);
    ~HMarkerChart();

public:
    void connectMarkers();
    void disconnectMarkers();
    void handleMarkerClicked();

protected:
    HMarkerChart(HMarkerChartPrivate &p, QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = 0);

protected:
    QScopedPointer<HMarkerChartPrivate> d_ptr;
};

#endif // HMARKERCHART_H
