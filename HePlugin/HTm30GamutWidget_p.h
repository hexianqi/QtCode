#pragma once

#include "HTm30GamutWidget.h"
#include "HCartesianWidget_p.h"

class HTm30GamutWidgetPrivate : public HCartesianWidgetPrivate
{
public:
    HTm30GamutWidgetPrivate();

public:
    QPolygonF polyTest;
    QPolygonF polyReference;

public:
    QImage cvg;
    QVector<QLineF> lineEdge;
    QVector<QRectF> rectHueBin;
};
