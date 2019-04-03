/***************************************************************************************************
**      2018-07-03  HZoomChartView 可缩放图表视图。
***************************************************************************************************/

#ifndef HZOOMCHARTVIEW_H
#define HZOOMCHARTVIEW_H


#include "HChartView.h"

class HZoomChartViewPrivate;

class QDESIGNER_WIDGET_EXPORT HZoomChartView : public HChartView
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HZoomChartView)

public:
    explicit HZoomChartView(QWidget *parent = nullptr);
    explicit HZoomChartView(QChart *chart, QWidget *parent = nullptr);
    ~HZoomChartView() override;

protected:
    HZoomChartView(HZoomChartViewPrivate &p, QChart *chart = nullptr, QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void keyPressEvent(QKeyEvent *) override;

private:
    void init();
};

#endif // HZOOMCHARTVIEW_H
