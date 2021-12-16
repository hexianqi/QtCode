#pragma once

#include "HTm30CvgWidget.h"
#include "HCartesianWidget_p.h"

class HTm30CvgWidgetPrivate : public HCartesianWidgetPrivate
{
public:
    HTm30CvgWidgetPrivate();

public:
    double Rf = 0.0;
    double Rg = 0.0;
    double CCT = 0.0;
    double Duv = 0.0;
    QPolygonF polyTest;
    QPolygonF polyReference;

public:
    QPixmap cvg;
    QList<QColor> colorQuiver;
    QVector<QLineF> lineEdge;
    QVector<QRectF> rectLabel;
};



