#pragma once

#include "HMainWindowDemo.h"
#include "HThreadDemo.h"
#include "HeData/HTestData.h"
#include "HePlugin/HSpecDiagramWidget.h"
#include <QtCharts/QLineSeries>

using namespace std;
QT_CHARTS_USE_NAMESPACE

class HMainWindowDemoPrivate
{
public:
    ITestData *testData;
    HThreadDemo *thread;
    vector<double> stdCurve;

public:
    QLineSeries *series1;
    QLineSeries *series2;
    HSpecDiagramWidget *specWidget;
};
