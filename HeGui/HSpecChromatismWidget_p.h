#ifndef HSPECCHROMATISMWIDGET_P_H
#define HSPECCHROMATISMWIDGET_P_H

#include "HSpecChromatismWidget.h"
#include "HeData/HDataGlobal.h"

class QMenu;
class HChromatismWidget;

HE_DATA_BEGIN_NAMESPACE
class IConfigManage;
class ITestData;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class IGuiFactory;

class HSpecChromatismWidgetPrivate
{
public:
    HSpecChromatismWidgetPrivate();

public:
    IGuiFactory *factory;
    IConfigManage *configManage;
    ITestData *testData;
    HChromatismWidget *chromatismWidget;
    QMenu *menuShow;
};

HE_GUI_END_NAMESPACE

#endif // HSPECCHROMATISMWIDGET_P_H
