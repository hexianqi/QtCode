/***************************************************************************************************
**      2018-07-03  HCie1931Chart CIE1931图表。
***************************************************************************************************/

#pragma once

#include "HSingleAxisChart.h"

class HCie1931ChartPrivate;

class HCie1931Chart : public HSingleAxisChart
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HCie1931Chart)

public:
    explicit HCie1931Chart(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());

signals:
    void pointFocusChanged(QPointF value);

public:
    void setEnableCIE(bool b);
    void setEnableHorseshoe(bool b);
    void setEnablePlanckian(bool b);
    void setEnableGrade(bool b);
    void setEnablePoint(bool b);

public:
    bool isEnableCIE();
    bool isEnableHorseshoe();
    bool isEnablePlanckian();
    bool isEnableGrade();
    bool isEnablePoint();

public:
    void setGradeFocus(QPolygonF);
    void setGrades(QList<QPolygonF>);
    void addGrade(QPolygonF value, bool focus = true);
    void clearGrade();
    void setPointFocus(QPointF);
    void setPoints(const QList<QPointF> &);
    void addPoint(QPointF value, bool focus = true);
    void clearPoint();

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    void init();
    void initAxes();
    void readSeries();
    void updateHorseshoeBrush();
};
