/***************************************************************************************************
**      2021-12-03  HTm30RfhjChartView
***************************************************************************************************/

#pragma once

#include "HZoomChartView.h"

class HTm30BarChart;
class HTm30RfhjChartViewPrivate;

class QDESIGNER_WIDGET_EXPORT HTm30RfhjChartView : public HZoomChartView
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTm30RfhjChartView)

public:
    explicit HTm30RfhjChartView(QWidget *parent = nullptr);
    ~HTm30RfhjChartView() override;

public:
    HTm30BarChart *chart();

protected:
    void init() override;
};



