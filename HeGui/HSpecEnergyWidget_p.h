#pragma once

#include "HSpecEnergyWidget.h"

class HSpecDiagramWidget;
class HProgressBar;
class QHBoxLayout;

HE_BEGIN_NAMESPACE

class ITestData;

class HSpecEnergyWidgetPrivate
{
public:
    HSpecEnergyWidgetPrivate();

public:
    bool ribbon = true;
    ITestData *testData = nullptr;
    HSpecDiagramWidget *specWidget = nullptr;
    QHBoxLayout *progressLayout = nullptr;
    QHash<QString, HProgressBar *> progressBars;
    QStringList toolTipTypes;
};

HE_END_NAMESPACE
