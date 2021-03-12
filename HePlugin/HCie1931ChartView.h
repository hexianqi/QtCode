/***************************************************************************************************
**      2018-07-03  HCIE1931View CIE1931视图。
***************************************************************************************************/

#pragma once

#include "HZoomChartView.h"

class HCie1931ChartViewPrivate;
class HCie1931Chart;

class QDESIGNER_WIDGET_EXPORT HCie1931ChartView : public HZoomChartView
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HCie1931ChartView)

public:
    explicit HCie1931ChartView(QWidget *parent = nullptr);

signals:
    void mouseDoubleClicked(QPointF point);

public:
    void setEnableTracking(bool b);

public:
    HCie1931Chart *chart();

protected:
    void init() override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

protected slots:
    void handlePlotAreaChanged(QRectF value);
    void handlePointFocusChanged(QPointF pos);
    void handlePositionChanged(QPointF pos);
};
