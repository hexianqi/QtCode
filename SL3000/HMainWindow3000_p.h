#pragma once

#include "HMainWindow3000.h"
#include <QtCore/QHash>

class HStationWidget;

class HMainWindow3000Private
{
public:
    HMainWindow3000Private();

public:
    bool showLogo = false;

public:
    QPixmap logo;

public:
    QToolBar *toolBarLogo = nullptr;

public:
    QVector<bool> stationEnable;
    QHash<int, HStationWidget *> stationWidget;
};
