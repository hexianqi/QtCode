#pragma once

#include "HPolarChartView.h"
#include "HChartView_p.h"

QT_CHARTS_BEGIN_NAMESPACE
class QPolarChart;
class QValueAxis;
class QSplineSeries;
QT_CHARTS_END_NAMESPACE

class QDESIGNER_WIDGET_EXPORT HPolarChartViewPrivate : public HChartViewPrivate
{
public:
    QPolarChart *chart = nullptr;
    QValueAxis *axisAngular = nullptr;
    QValueAxis *axisRadial = nullptr;
    QSplineSeries *series = nullptr;
};



