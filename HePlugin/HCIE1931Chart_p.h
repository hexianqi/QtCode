#ifndef HCIE1931CHART_P_H
#define HCIE1931CHART_P_H

#include "HCIE1931Chart.h"
#include "HSingleAxisChart_p.h"

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QAreaSeries;
class QScatterSeries;
QT_CHARTS_END_NAMESPACE

class HCIE1931ChartPrivate : HSingleAxisChartPrivate
{
    Q_DECLARE_PUBLIC(HCIE1931Chart)

public:
    HCIE1931ChartPrivate(HCIE1931Chart *q);

public:
    QImage getCrossImage(QPen pen);

public:
    QPixmap cie;
    QAreaSeries *horseshoe;
    QLineSeries *planckian;
    QScatterSeries *pointFocus;
    QScatterSeries *points;
    QLineSeries *gradeFocus;
    QList<QLineSeries *> grades;
    bool enableCIE = true;
    bool enableHorseshoe = true;
    bool enablePlanckian = true;
    bool enableGrade = true;
    bool enablePoint = true;
};

#endif // HCIE1931CHART_P_H
