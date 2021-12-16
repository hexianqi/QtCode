#pragma once

#include "HAbstractTestWidget.h"

HE_BEGIN_NAMESPACE

class ITestData;
class IModel;
class ITestSetWidget;

class HAbstractTestWidgetPrivate
{
public:
    HAbstractTestWidgetPrivate();

public:
    ITestSetWidget *testSetWidget = nullptr;
    IModel *model;
    ITestData *testData;
    QList<QMenu *> menus;
    QList<QToolBar *> toolBars;
};

HE_END_NAMESPACE
