/***************************************************************************************************
**      2019-04-08  HSpecSampleChartView 光谱采样图表。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include "HePlugin/HVernierChartView.h"

HE_BEGIN_NAMESPACE

class HSpecSampleChartViewPrivate;

class HSpecSampleChartView : public HVernierChartView
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecSampleChartView)

public:
    explicit HSpecSampleChartView(QWidget *parent = nullptr);
    ~HSpecSampleChartView() override;

public:
    void setEnablePeak(bool b);
    void refreshWidget();
    void refreshCenter();
    void refreshRight();

protected slots:
    void setVernier(const QList<double> &value);

protected:
    void init() override;
};

HE_END_NAMESPACE
