#pragma once

#include "HStationWidget.h"

class QToolBar;
class QStackedWidget;
class HTestTricrystal;
class HTestResultWidget;
class HTestConfigWidget;

class HStationWidgetPrivate
{
public:
    int index;

public:
    HTestTricrystal *testData = nullptr;

public:
    QAction *actionStart = nullptr;
    QAction *actionStop = nullptr;
    QAction *actionSetp = nullptr;
    QAction *actionClear = nullptr;
    QAction *actionCie = nullptr;
    QAction *actionEnergy = nullptr;
    QAction *actionTestResult = nullptr;
    QAction *actionTestConfig = nullptr;
    QToolBar *toolBar = nullptr;
    QStackedWidget *stackedWidget = nullptr;
    HTestResultWidget *testResultWidget = nullptr;
    HTestConfigWidget *testConfigWidget = nullptr;
};



