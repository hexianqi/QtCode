#ifndef HSPECCHROMATISMCHARTVIEW_P_H
#define HSPECCHROMATISMCHARTVIEW_P_H

#include "HSpecChromatismChartView.h"
#include "HePlugin/HChromatismChartView_p.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class IConfigManage;
class ITestData;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

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

HE_GUI_END_NAMESPACE

#endif // HSPECCHROMATISMCHARTVIEW_P_H
