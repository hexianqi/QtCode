/***************************************************************************************************
**      2021-12-21  HTm30RfRgChartView
***************************************************************************************************/

#pragma once

#include "HZoomChartView.h"

class HTm30RfRgChartViewPrivate;

class QDESIGNER_WIDGET_EXPORT HTm30RfRgChartView : public HZoomChartView
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HTm30RfRgChartView)

public:
    explicit HTm30RfRgChartView(QWidget *parent = nullptr);
    ~HTm30RfRgChartView() override;

public:
    void setRfRg(double Rf, double Rg);

protected:
    void init() override;
};



