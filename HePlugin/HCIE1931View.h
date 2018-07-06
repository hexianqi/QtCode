/***************************************************************************************************
**      2018-07-03  HCIE1931View CIE1931视图。
***************************************************************************************************/

#ifndef HCIE1931VIEW_H
#define HCIE1931VIEW_H

#include "HZoomChartView.h"

class HCIE1931ViewPrivate;
class HCIE1931Chart;
class HPositionTracking;

class QDESIGNER_WIDGET_EXPORT HCIE1931View : public HZoomChartView
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HCIE1931View)

public:
    explicit HCIE1931View(QWidget *parent = nullptr);
    ~HCIE1931View();

signals:
    void mouseDoubleClicked(QPointF point);

public:
    void setEnableTracking(bool b);

public:
    HCIE1931Chart *cieChart();

protected:
    virtual void mouseMoveEvent(QMouseEvent *) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

protected slots:
    void handlePlotAreaChanged(QRectF value);
    void handlePointFocusChanged(QPointF pos);
    void handlePositionChanged(QPointF pos);

private:
    void init();
};

#endif // HCIE1931VIEW_H
