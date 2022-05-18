#pragma once

#include "HAbstractChartExtend.h"

class HAbstractChartExtendPrivate
{
public:
    HAbstractChartExtendPrivate(QChart *p = nullptr);

public:
    QChart *chart = nullptr;
    QList<QAction *> actions;
};

