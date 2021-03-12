/***************************************************************************************************
**      2018-07-03  HZoomChartView 可缩放图表视图。
***************************************************************************************************/

#pragma once

#include "HChartView.h"

class HZoomChartViewPrivate;

class QDESIGNER_WIDGET_EXPORT HZoomChartView : public HChartView
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HZoomChartView)

public:
    explicit HZoomChartView(QWidget *parent = nullptr);
    explicit HZoomChartView(QChart *chart, QWidget *parent = nullptr);

protected:
    HZoomChartView(HZoomChartViewPrivate &p, QChart *chart = nullptr, QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void keyPressEvent(QKeyEvent *) override;

protected:
    virtual void init();
};
