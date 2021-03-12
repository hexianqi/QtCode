#pragma once

#include "HResultTableWidget.h"
#include "HeData/HDataGlobal.h"
#include "HePlugin/HEntireTableWidget_p.h"

class HOptionalTableExtend;

HE_DATA_BEGIN_NAMESPACE
class ITestData;
HE_DATA_END_NAMESPACE
HE_DATA_USE_NAMESPACE

HE_GUI_BEGIN_NAMESPACE

class HResultTableWidgetPrivate : public HEntireTableWidgetPrivate
{
public:
    HResultTableWidgetPrivate();

public:
    ITestData *testData = nullptr;
    HOptionalTableExtend *optional = nullptr;
    QStringList displays;
};

HE_GUI_END_NAMESPACE
