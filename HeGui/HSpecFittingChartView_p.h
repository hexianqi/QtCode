#pragma once

#include "HSpecFittingChartView.h"
#include "HePlugin/HZoomChartView_p.h"

class HSingleAxisChart;
class HMarkerChartExtend;
class HCalloutChartExtend;

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QScatterSeries;
QT_CHARTS_END_NAMESPACE
QT_CHARTS_USE_NAMESPACE

HE_BEGIN_NAMESPACE

class HSpecFittingChartViewPrivate : public HZoomChartViewPrivate
{
public:
    HSingleAxisChart *chart;
    HMarkerChartExtend *marker;
    HCalloutChartExtend *callout;
    QHash<int, QLineSeries *> lineSeries;
    QHash<int, QScatterSeries *> scatterSeries;
};

HE_END_NAMESPACE
