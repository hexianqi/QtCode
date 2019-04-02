/***************************************************************************************************
**      2019-04-02  HVernierChartView   游标视图。
***************************************************************************************************/

#ifndef HVERNIERCHARTVIEW_H
#define HVERNIERCHARTVIEW_H

#include "HZoomChartView.h"

class HVernierChartViewPrivate;
class HGraphicsVernierTracking;

class QDESIGNER_WIDGET_EXPORT HVernierChartView : public HZoomChartView
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HVernierChartView)

public:
    explicit HVernierChartView(QWidget *parent = nullptr);
    explicit HVernierChartView(QChart *chart, QWidget *parent = nullptr);
    ~HVernierChartView() override;

signals:
    void vernierValueChanged(QVector<double> value);
    void vernierTextChanged(QString value);

public:
    void setDecimals(int value);

public:
    HGraphicsVernierTracking *tracking();
    int decimals();

protected:
    HVernierChartView(HVernierChartViewPrivate &p, QChart *chart = nullptr, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void handlePlotAreaChanged(QRectF value);
    void updataVernier();

private:
    void init();
};

#endif // HVERNIERCHARTVIEW_H
