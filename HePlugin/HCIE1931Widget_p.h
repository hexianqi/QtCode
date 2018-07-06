#ifndef HCIE1931WIDGET_P_H
#define HCIE1931WIDGET_P_H

#include "HCIE1931Widget.h"
#include "HCartesianWidget_p.h"

class QLabel;
class HPositionTracking;

class HCIE1931WidgetPrivate : public HCartesianWidgetPrivate
{
    Q_DECLARE_PUBLIC(HCIE1931Widget)

public:
    HCIE1931WidgetPrivate(HCIE1931Widget *q);

public:
    void readStandard();

public:
    HPositionTracking *tracking;
    QLabel *label;
    bool drawCIE = true;
    bool drawHorseshoe = true;
    bool drawPlanckian = true;
    bool drawGrade = true;
    bool drawPoint = true;
    QColor colorHorseshoe = Qt::black;
    QColor colorPlanckian = Qt::black;
    QColor colorGrade = Qt::black;
    QColor colorGradeFocus = Qt::red;
    QColor colorPoint = Qt::black;
    QColor colorPointFocus = Qt::red;
    QFont fontPointFocus;
    QPixmap cie1931;
    QPolygonF horseshoe;
    QPolygonF planckian;
    QList<QPolygonF> grade;
    QPolygonF gradeFocus;
    QList<QPointF> point;
    QPointF pointFocus;
    QAction *actionCIE;
    QAction *actionHorseshoe;
    QAction *actionPlanckian;
    QAction *actionGrade;
    QAction *actionPoint;
    QAction *actionClearPoint;
};

#endif // HCIE1931WIDGET_P_H
