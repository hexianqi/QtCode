#pragma once

#include "HMainWindow3000.h"
#include <QtCore/QHash>

class QLabel;
class HStationWidget;
class HStatusWidget;

class HMainWindow3000Private
{
public:
    HMainWindow3000Private();

public:
    bool showLogo = false;
    QVector<bool> stationEnable;

public:
    QPixmap logo;

public:
    QToolBar *toolBarLogo = nullptr;

public:
    QTimer *timer = nullptr;
    QLabel *time = nullptr;
    HStatusWidget *workStatusWidget = nullptr;
    HStatusWidget *specStatusWidget = nullptr;
    HStatusWidget *elecStatusWidget = nullptr;
    QHash<int, HStationWidget *> stationWidget;
};
