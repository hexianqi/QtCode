#pragma once

#include "HTestWidget1000RGB.h"
#include "HeGui/HTestWidget_p.h"

class HTestResult1000RGB;
class HCie1931Widget;
class HCartesianWidget;

HE_BEGIN_NAMESPACE
class HResultTableWidget;
HE_END_NAMESPACE

class HTestWidget1000RGBPrivate : public HTestWidgetPrivate
{
public:
    HTestWidget1000RGBPrivate();

public:
    HTestResult1000RGB *testResult = nullptr;

public:
    HCie1931Widget *cieWidget = nullptr;
    HCartesianWidget *energyWidget = nullptr;
    QHash<int, HResultTableWidget *> tableWidgets;

public:
    QHash<int, QStringList> displays;
};
