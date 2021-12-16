/***************************************************************************************************
**      2019-05-21  HSpecChromatismChartView 色容差图表。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include "HePlugin/HChromatismChartView.h"

HE_BEGIN_NAMESPACE

class HSpecChromatismChartViewPrivate;

class HSpecChromatismChartView : public HChromatismChartView
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HSpecChromatismChartView)

public:
    explicit HSpecChromatismChartView(QWidget *parent = nullptr);
    ~HSpecChromatismChartView() override;

public:
    void initMenuShow();
    void refreshWidget();

protected:
    void init() override;
    void showChromatism(QAction *);
};

HE_END_NAMESPACE
