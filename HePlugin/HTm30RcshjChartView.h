/***************************************************************************************************
**      2021-12-03  HTm30RcshjChartView
***************************************************************************************************/

#pragma once

#include "HZoomChartView.h"

class HTm30BarChart;
class HTm30RcshjChartViewPrivate;

class QDESIGNER_WIDGET_EXPORT HTm30RcshjChartView : public HZoomChartView
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTm30RcshjChartView)

public:
    explicit HTm30RcshjChartView(QWidget *parent = nullptr);
    ~HTm30RcshjChartView() override;

public:
    HTm30BarChart *chart();

protected:
    void init() override;
};



