/***************************************************************************************************
**      2019-05-21  HChromatismChartView 色容差视图。
***************************************************************************************************/

#pragma once

#include "HZoomChartView.h"

class HChromatismChart;
class HChromatismChartViewPrivate;

class QDESIGNER_WIDGET_EXPORT HChromatismChartView : public HZoomChartView
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HChromatismChartView)

public:
    explicit HChromatismChartView(QWidget *parent = nullptr);

public:
    HChromatismChart *chart();
    void setData(const QVariantMap &);

protected:
    HChromatismChartView(HChromatismChartViewPrivate &p, QWidget *parent = nullptr);

protected slots:
    void handlePlotAreaChanged(QRectF value);

protected:
    void init() override;
};
