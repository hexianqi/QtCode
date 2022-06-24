#pragma once

#include "HChromatismChartView.h"
#include "HZoomChartView_p.h"

class QGraphicsSimpleTextItem;
class HSingleAxisChart;

QT_CHARTS_BEGIN_NAMESPACE
class QValueAxis;
class QLineSeries;
class QScatterSeries;
QT_CHARTS_END_NAMESPACE

class HChromatismChartViewPrivate : public HZoomChartViewPrivate
{
public:
    QGraphicsSimpleTextItem *pointFocusItem = nullptr;

public:
    HSingleAxisChart *chart = nullptr;
    QValueAxis *axisX = nullptr;
    QValueAxis *axisY = nullptr;
    QLineSeries *ellipse = nullptr;
    QScatterSeries *focus = nullptr;
    QScatterSeries *center = nullptr;

public:
    QPointF pointCenter;
    double sdcmStd = 0.0;
    double theta = 0.0;
    double axisA = 0.0;
    double axisB = 0.0;
    QPointF pointFocus;
    double sdcmFocus = 0.0;
};
