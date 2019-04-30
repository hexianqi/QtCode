/***************************************************************************************************
**      2019-04-01  HSpecFittingChartView 光谱拟合图表。
***************************************************************************************************/

#ifndef HSPECFITTINGCHARTVIEW_H
#define HSPECFITTINGCHARTVIEW_H

#include "HGuiGlobal.h"
#include "HePlugin/HZoomChartView.h"

HE_GUI_BEGIN_NAMESPACE

class HSpecFittingChartViewPrivate;

class HSpecFittingChartView : public HZoomChartView
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecFittingChartView)

public:
    explicit HSpecFittingChartView(QWidget *parent = nullptr);
    ~HSpecFittingChartView() override;

public:
    void addSeries(int id, QPolygonF value);
    void removeSeries(int id);
    void clearSeries();

protected:
    void init() override;
    void resizeEvent(QResizeEvent *) override;
};

HE_GUI_END_NAMESPACE

#endif // HSPECFITTINGCHARTVIEW_H
