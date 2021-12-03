/***************************************************************************************************
**      2021-12-01  HTm30RfiChartView
***************************************************************************************************/

#pragma once

#include "HZoomChartView.h"

class HTm30BarChart;
class HTm30RfiChartViewPrivate;

class QDESIGNER_WIDGET_EXPORT HTm30RfiChartView : public HZoomChartView
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTm30RfiChartView)

public:
    explicit HTm30RfiChartView(QWidget *parent = nullptr);
    ~HTm30RfiChartView() override;

public:
    HTm30BarChart *chart();

protected:
    void init() override;
    void readColor();
};



