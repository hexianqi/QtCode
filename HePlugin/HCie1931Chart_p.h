#pragma once

#include "HCie1931Chart.h"
#include "HSingleAxisChart_p.h"

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QAreaSeries;
class QScatterSeries;
QT_CHARTS_END_NAMESPACE

class HCie1931ChartPrivate : public HSingleAxisChartPrivate
{
public:
    HCie1931ChartPrivate();

public:
    QPixmap cie;
    QAreaSeries *horseshoe = nullptr;
    QLineSeries *planckian = nullptr;
    QScatterSeries *pointFocus = nullptr;
    QScatterSeries *point = nullptr;
    QLineSeries *gradeFocus = nullptr;
    QList<QLineSeries *> grades;
    bool enableCIE = true;
    bool enableHorseshoe = true;
    bool enablePlanckian = true;
    bool enableGrade = true;
    bool enablePoint = true;
};
