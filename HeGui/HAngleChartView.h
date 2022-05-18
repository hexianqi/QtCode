/***************************************************************************************************
**      2022-05-16  HAngleChartView
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include "HePlugin/HPolarChartView.h"

HE_BEGIN_NAMESPACE

class HAngleChartViewPrivate;

class HAngleChartView : public HPolarChartView
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAngleChartView)

public:
    explicit HAngleChartView(QWidget *parent = nullptr);
    ~HAngleChartView() override;

public:
    void setAngleFifth(double left, double right);
    void setAngleHalf(double left, double right);

protected:
    HAngleChartView(HAngleChartViewPrivate &p, QWidget *parent = nullptr);

protected:
    void init() override;
    void resizeEvent(QResizeEvent *) override;
};

HE_END_NAMESPACE

