#pragma once

#include "HAbstractTestWidget.h"

HE_BEGIN_NAMESPACE

class IModel;
class ITestData;
class IMemento;
class ITestSetWidget;

class HAbstractTestWidgetPrivate
{
public:
    HAbstractTestWidgetPrivate();

public:
    IModel *model;
    ITestData *testData;
    IMemento *memento = nullptr;
    ITestSetWidget *testSetWidget = nullptr;
    QList<QMenu *> menus;
    QList<QToolBar *> toolBars;
    bool running = false;
};

HE_END_NAMESPACE
