/***************************************************************************************************
**      2021-12-03  HTm30RhshjChartView
***************************************************************************************************/

#pragma once

#include "HZoomChartView.h"

class HTm30BarChart;
class HTm30RhshjChartViewPrivate;

class QDESIGNER_WIDGET_EXPORT HTm30RhshjChartView : public HZoomChartView
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTm30RhshjChartView)

public:
    explicit HTm30RhshjChartView(QWidget *parent = nullptr);
    ~HTm30RhshjChartView() override;

public:
    HTm30BarChart *chart();

protected:
    void init() override;
};


