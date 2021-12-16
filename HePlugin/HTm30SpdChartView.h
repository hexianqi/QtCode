/***************************************************************************************************
**      2021-12-14  HTm30SpdChartView
***************************************************************************************************/

#pragma once

#include "HZoomChartView.h"

class HTm30SpdChartViewPrivate;

class QDESIGNER_WIDGET_EXPORT HTm30SpdChartView : public HZoomChartView
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTm30SpdChartView)

public:
    explicit HTm30SpdChartView(QWidget *parent = nullptr);
    ~HTm30SpdChartView() override;

public:
    void setAxisXRange(double min, double max);
    void setTest(QPolygonF);
    void setReference(QPolygonF);

protected:
    void init() override;
};



