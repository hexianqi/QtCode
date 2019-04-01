/***************************************************************************************************
**      2018-07-03  HZoomChartView 可缩放视图。
***************************************************************************************************/

#ifndef HZOOMCHARTVIEW_H
#define HZOOMCHARTVIEW_H

#include <QtUiPlugin/QDesignerExportWidget>
#include <QtCharts/QChartView>

QT_CHARTS_USE_NAMESPACE

class HZoomChartViewPrivate;

class QDESIGNER_WIDGET_EXPORT HZoomChartView : public QChartView
{
    Q_OBJECT

public:
    explicit HZoomChartView(QWidget *parent = nullptr);
    explicit HZoomChartView(QChart *chart, QWidget *parent = nullptr);
    ~HZoomChartView() override;

protected:
    HZoomChartView(HZoomChartViewPrivate &p, QWidget *parent = nullptr);

protected:
    virtual void resizeEvent(QResizeEvent *) override;
    virtual void mouseReleaseEvent(QMouseEvent *) override;
    virtual void keyPressEvent(QKeyEvent *) override;

protected:
    QScopedPointer<HZoomChartViewPrivate> d_ptr;

private:
    void init();
};

#endif // HZOOMCHARTVIEW_H
