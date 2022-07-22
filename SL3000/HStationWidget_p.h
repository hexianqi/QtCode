#pragma once

#include "HStationWidget.h"

class QToolBar;
class QStackedWidget;
class HTestWidget3000;
class HTestSetWidget3000;

class HStationWidgetPrivate
{
public:
    int index;

public:
    QAction *actionStart = nullptr;
    QAction *actionStop = nullptr;
    QAction *actionSetp = nullptr;
    QAction *actionClear = nullptr;
    QAction *actionCie = nullptr;
    QAction *actionEnergy = nullptr;
    QAction *actionTest = nullptr;
    QAction *actionTestSet = nullptr;
    QToolBar *toolBar = nullptr;
    QStackedWidget *stackedWidget = nullptr;
    HTestWidget3000 *testWidget = nullptr;
    HTestSetWidget3000 *testSetWidget = nullptr;
};



