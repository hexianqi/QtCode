#pragma once

#include "HAbstractTestSetWidget.h"

HE_BEGIN_NAMESPACE

class ITestData;
class IModel;

class HAbstractTestSetWidgetPrivate
{
public:
    HAbstractTestSetWidgetPrivate();

public:
    IModel *model;
    ITestData *testData;
    QVariantMap datas;
    bool testState = false;
    int testMode = 0;
    int saveMode = 0;
};

HE_END_NAMESPACE
