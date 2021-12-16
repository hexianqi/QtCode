#pragma once

#include "HSpecChromatismWidget.h"

class QMenu;
class HChromatismWidget;

HE_BEGIN_NAMESPACE

class IConfigManage;
class ITestData;
class IGuiFactory;

class HSpecChromatismWidgetPrivate
{
public:
    HSpecChromatismWidgetPrivate();

public:
    IGuiFactory *factory = nullptr;
    IConfigManage *configManage = nullptr;
    ITestData *testData = nullptr;
    HChromatismWidget *chromatismWidget = nullptr;
    QMenu *menuShow = nullptr;
};

HE_END_NAMESPACE
