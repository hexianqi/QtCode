/***************************************************************************************************
**      2022-04-11  HPolarChartView
***************************************************************************************************/

#pragma once

#include "HChartView.h"

QT_CHARTS_BEGIN_NAMESPACE
class QValueAxis;
QT_CHARTS_END_NAMESPACE

class HPolarChartViewPrivate;

class QDESIGNER_WIDGET_EXPORT HPolarChartView : public HChartView
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HPolarChartView)

public:
    explicit HPolarChartView(QWidget *parent = nullptr);
    ~HPolarChartView() override;

public:
    QValueAxis *axisAngular();
    QValueAxis *axisRadial();

public:
    void clear();
    void replace(QVector<QPointF>);

protected:
    HPolarChartView(HPolarChartViewPrivate &p, QWidget *parent = nullptr);

protected:
    void init() override;
};



