#ifndef HCIE1931CHART_H
#define HCIE1931CHART_H

#include <QtCharts/QChart>

QT_CHARTS_USE_NAMESPACE

class HCIE1931ChartPrivate;

class HCIE1931Chart : public QChart
{
    Q_OBJECT

public:
    explicit HCIE1931Chart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    ~HCIE1931Chart();

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
    void setGradeFocus(QPolygonF value);
    void setGrades(QList<QPolygonF> value);
    void addGrade(QPolygonF value, bool focus = true);
    void clearGrade();
    void setPointFocus(QPointF value);
    void setPoints(QList<QPointF> value);
    void addPoint(QPointF value, bool focus = true);
    void clearPoint();

protected:
    QScopedPointer<HCIE1931ChartPrivate> d_ptr;

private:
    void initSeries();
    void initAxes();
    void initLegend();
    void updateHorseshoeBrush();
};

#endif // HCIE1931CHART_H
