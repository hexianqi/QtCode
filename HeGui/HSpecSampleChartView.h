/***************************************************************************************************
**      2019-04-08  HSpecSampleChartView 光谱采样图表。
***************************************************************************************************/

#ifndef HSPECSAMPLECHARTVIEW_H
#define HSPECSAMPLECHARTVIEW_H

#include "HGuiGlobal.h"
#include "HePlugin/HVernierChartView.h"

HE_GUI_BEGIN_NAMESPACE

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
    void setVernier(QList<double> value);

protected:
    void init() override;
};

HE_GUI_END_NAMESPACE

#endif // HSPECSAMPLECHARTVIEW_H
