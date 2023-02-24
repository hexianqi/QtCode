#pragma once

#include "HTestResult1000RGB.h"
#include <QtCore/QHash>

class HTestResult1000RGBPrivate
{
public:
    HTestResult1000RGBPrivate();

public:
    ITestData *testData = nullptr;
    QHash<int, QList<ITestData *>> results;
};



