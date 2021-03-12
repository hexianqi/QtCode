/***************************************************************************************************
**      2019-04-11  HChart 自定义D指针图表。
***************************************************************************************************/

#pragma once

#include <QtUiPlugin/QDesignerExportWidget>
#include <QtCharts/QChart>

QT_CHARTS_USE_NAMESPACE

class HChartPrivate;

class QDESIGNER_WIDGET_EXPORT HChart : public QChart
{
    Q_OBJECT

public:
    explicit HChart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
    ~HChart() override;

protected:
    HChart(HChartPrivate &p, QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());

protected:
    QScopedPointer<HChartPrivate> d_ptr;
};
