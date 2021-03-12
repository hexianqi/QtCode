#pragma once

#include "HChromatismChart.h"
#include "HChart_p.h"

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QScatterSeries;
QT_CHARTS_END_NAMESPACE

class HChromatismChartPrivate : public HChartPrivate
{
public:
    HChromatismChartPrivate();

public:
    QLineSeries *ellipse = nullptr;
    QScatterSeries *focus = nullptr;
    QScatterSeries *center = nullptr;
};
