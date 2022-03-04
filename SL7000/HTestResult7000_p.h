#pragma once

#include "HTestResult7000.h"
#include "HeCore/.h"
#include <QtGui/QPolygon>

class HTestResult7000Private
{
public:
    HTestResult7000Private();

public:
    bool modified = false;
    QPolygon polygon;
    ITestData *testData = nullptr;
    QHash<QPoint, ITestData *> results;
};
