#pragma once

#include "HPolarChartView.h"
#include "HChartView_p.h"

class HSingleAxisChart;

QT_CHARTS_BEGIN_NAMESPACE
class QPolarChart;
class QValueAxis;
class QSplineSeries;
QT_CHARTS_END_NAMESPACE

class QDESIGNER_WIDGET_EXPORT HPolarChartViewPrivate : public HChartViewPrivate
{
public:
    QPolarChart *chart;
    QValueAxis *axisAngular;
    QValueAxis *axisRadial;
    QSplineSeries *series;
};



