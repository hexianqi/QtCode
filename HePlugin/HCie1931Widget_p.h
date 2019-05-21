#ifndef HCIE1931WIDGET_P_H
#define HCIE1931WIDGET_P_H

#include "HCie1931Widget.h"
#include "HCartesianWidget_p.h"

class QLabel;
class HPositionTracking;

class HCie1931WidgetPrivate : public HCartesianWidgetPrivate
{
    Q_DECLARE_PUBLIC(HCie1931Widget)

public:
    HCie1931WidgetPrivate(HCie1931Widget *);

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
    QList<QPolygonF> grades;
    QPolygonF gradeFocus;
    QList<QPointF> points;
    QPointF pointFocus;
};

#endif // HCIE1931WIDGET_P_H
