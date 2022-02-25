#pragma once

#include "HTestResult7000.h"
#include <QtGui/QPolygon>

class HTestResult7000Private
{
public:
    HTestResult7000Private();

public:
    bool modified = false;
    QPolygon polygon;
    QList<ITestData *> results;
};



