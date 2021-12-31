#pragma once

#include "HDiagramWidget.h"

class HDiagramWidgetPrivate
{
public:
    HDiagramWidgetPrivate();

public:
    QRectF calcPlotArea(QSize size);

public:
    QPixmap pixmap;
    QMargins margins = QMargins(50, 50, 50, 50);
    QRectF plotArea;
    QBrush brushBackground = Qt::NoBrush;
    QBrush brushPlotArea = Qt::NoBrush;
    bool square = false;
    bool halfSide = false;
    bool drawFrame = true;
    bool drawRuler = true;
    bool drawTick = true;
    bool drawGrid = true;
    QColor colorFrame = Qt::black;
    QColor colorRuler = Qt::black;
    QColor colorGrid = QColor(128, 128, 128, 128);
    QHash<int, QColor> polygonColors;
    QHash<int, QPolygonF> polygons;
};
