#pragma once

#include "HDynamicChartView.h"
#include "HZoomChartView_p.h"

class HMarkerChartExtend;
class HCalloutChartExtend;
class HSingleAxisChart;

QT_CHARTS_BEGIN_NAMESPACE
class QValueAxis;
class QLineSeries;
class QScatterSeries;
QT_CHARTS_END_NAMESPACE

class QDESIGNER_WIDGET_EXPORT HDynamicChartViewPrivate : public HZoomChartViewPrivate
{
public:
    HSingleAxisChart *chart;
    QValueAxis *axisX;
    QValueAxis *axisY;
    QLineSeries *lineSeries;
    QScatterSeries *scatterSeries;
    HMarkerChartExtend *marker;
    HCalloutChartExtend *callout;
};
