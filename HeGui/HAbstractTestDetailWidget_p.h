#pragma once

#include "HAbstractTestDetailWidget.h"

HE_BEGIN_NAMESPACE

class ITestData;

class HAbstractTestDetailWidgetPrivate
{
public:
    HAbstractTestDetailWidgetPrivate();

public:
    ITestData *testData;
};

HE_END_NAMESPACE
