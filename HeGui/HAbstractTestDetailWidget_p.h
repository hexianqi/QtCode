#pragma once

#include "HAbstractTestDetailWidget.h"
#include "HeData/HDataGlobal.h"

HE_DATA_BEGIN_NAMESPACE
class ITestData;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HE_GUI_EXPORT HAbstractTestDetailWidgetPrivate
{
public:
    HAbstractTestDetailWidgetPrivate();

public:
    ITestData *testData;
};

HE_GUI_END_NAMESPACE
