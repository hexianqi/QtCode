#pragma once

#include "HResultTableWidget.h"
#include "HePlugin/HEntireTableWidget_p.h"

class HOptionalTableExtend;

HE_BEGIN_NAMESPACE

class ITestData;

class HResultTableWidgetPrivate : public HEntireTableWidgetPrivate
{
public:
    HResultTableWidgetPrivate();

public:
    ITestData *testData = nullptr;
    HOptionalTableExtend *optional = nullptr;
    QStringList displays;
};

HE_END_NAMESPACE
