/***************************************************************************************************
**      2019-04-02  HChartView 自定义图表视图。
***************************************************************************************************/

#pragma once

#include <QtUiPlugin/QDesignerExportWidget>
#include <QtCharts/QChartView>

QT_CHARTS_USE_NAMESPACE

class HChartViewPrivate;

class QDESIGNER_WIDGET_EXPORT HChartView : public QChartView
{
    Q_OBJECT

public:
    explicit HChartView(QWidget *parent = nullptr);
    explicit HChartView(QChart *chart, QWidget *parent = nullptr);
    ~HChartView() override;

protected:
    HChartView(HChartViewPrivate &p, QChart *chart = nullptr, QWidget *parent = nullptr);

protected:
    QScopedPointer<HChartViewPrivate> d_ptr;
};
