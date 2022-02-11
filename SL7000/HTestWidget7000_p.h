#pragma once

#include "HTestWidget7000.h"
#include "HeGui\HTestWidget_p.h"

class HCie1931Widget;
class HTm30SpdChartView;
class HTm30CvgWidget;
class HTm30GamutWidget;
class HTm30RfRgChartView;
class HTm30RfiChartView;
class HTm30RfhjChartView;
class HTm30RcshjChartView;
class HTm30RhshjChartView;

class HTestResult7000;

HE_BEGIN_NAMESPACE
class IConfigManage;
class HSpecEnergyWidget;
class HSpecChromatismChartView;
class HResultTableWidget;
class ITestDetailWidget;
HE_END_NAMESPACE

class HTestWidget7000Private : public HTestWidgetPrivate
{
public:
    HTestWidget7000Private();

public:
    HCie1931Widget *cieWidget = nullptr;
    HTm30SpdChartView *spdWidget = nullptr;
    HTm30CvgWidget *cvgWidget = nullptr;
    HTm30GamutWidget *gamutWidget = nullptr;
    HTm30RfRgChartView *rfrgWidget = nullptr;
    HTm30RfiChartView *rfiWidget = nullptr;
    HTm30RfhjChartView *rfhjWidget = nullptr;
    HTm30RcshjChartView *rcshjWidget = nullptr;
    HTm30RhshjChartView *rhshjWidget = nullptr;
    HSpecEnergyWidget *energyWidget = nullptr;
    HSpecChromatismChartView *chromatismWidget = nullptr;
    HResultTableWidget *tableWidget = nullptr;
    ITestDetailWidget *detailWidget = nullptr;

public:
    IConfigManage *configManage = nullptr;
    HTestResult7000 *testResult = nullptr;

public:
    QStringList displays;
    QStringList tableSelecteds;
};

