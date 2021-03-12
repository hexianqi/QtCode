#pragma once

#include "HCie1931Widget.h"
#include "HCartesianWidget_p.h"

class QLabel;
class HPositionTracking;

class HCie1931WidgetPrivate : public HCartesianWidgetPrivate
{
public:
    HCie1931WidgetPrivate();

public:
    void readStandard();

public:
    HPositionTracking *tracking = nullptr;
    QLabel *label = nullptr;
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
