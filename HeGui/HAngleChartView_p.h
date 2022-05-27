#pragma once

#include "HAngleChartView.h"
#include "HePlugin/HPolarChartView_p.h"

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
QT_CHARTS_END_NAMESPACE

HE_BEGIN_NAMESPACE

class HAngleChartViewPrivate : public HPolarChartViewPrivate
{
public:
    double maxValue = 999999.0;
    QLineSeries *originSeries = nullptr;
    QLineSeries *fifthSeries = nullptr;
    QLineSeries *halfSeries = nullptr;
};

HE_END_NAMESPACE

