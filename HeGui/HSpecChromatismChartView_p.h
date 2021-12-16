#pragma once

#include "HSpecChromatismChartView.h"
#include "HePlugin/HChromatismChartView_p.h"

HE_BEGIN_NAMESPACE

class IConfigManage;
class ITestData;
class IGuiFactory;

class HSpecChromatismChartViewPrivate : public HChromatismChartViewPrivate
{
public:
    HSpecChromatismChartViewPrivate();

public:
    IGuiFactory *factory = nullptr;
    IConfigManage *configManage = nullptr;
    ITestData *testData = nullptr;
    QMenu *menuShow = nullptr;
};

HE_END_NAMESPACE
