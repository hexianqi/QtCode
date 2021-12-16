/***************************************************************************************************
**      2019-04-01  HSpecFittingChartView 光谱拟合图表。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include "HePlugin/HZoomChartView.h"

HE_BEGIN_NAMESPACE

class HSpecFittingChartViewPrivate;

class HSpecFittingChartView : public HZoomChartView
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecFittingChartView)

public:
    explicit HSpecFittingChartView(QWidget *parent = nullptr);
    ~HSpecFittingChartView() override;

public:
    void addLineSeries(int id, const QPolygonF &value);
    void removeLineSeries(int id);
    void addScatterSeries(int id, const QPolygonF &value);
    void removeScatterSeries(int id);
    void clearSeries();

protected:
    void init() override;
    void resizeEvent(QResizeEvent *) override;
};

HE_END_NAMESPACE
