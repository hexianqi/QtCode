/***************************************************************************************************
**      2019-05-21  HSpecChromatismChartView 色容差图表。
***************************************************************************************************/

#ifndef HSPECCHROMATISMCHARTVIEW_H
#define HSPECCHROMATISMCHARTVIEW_H

#include "HGuiGlobal.h"
#include "HePlugin/HChromatismChartView.h"

HE_GUI_BEGIN_NAMESPACE

class HSpecChromatismChartViewPrivate;

class HE_GUI_EXPORT HSpecChromatismChartView : public HChromatismChartView
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

HE_GUI_END_NAMESPACE

#endif // HSPECCHROMATISMCHARTVIEW_H
