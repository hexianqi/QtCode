#ifndef HDIAGRAMWIDGET_P_H
#define HDIAGRAMWIDGET_P_H

#include "HDiagramWidget.h"

class HDiagramWidgetPrivate
{
public:
    HDiagramWidgetPrivate(HDiagramWidget *q);

public:
    QRectF calcPlotArea(QSize size);

public:
    HDiagramWidget *q_ptr;
    QPixmap pixmap;
    QMargins margins = QMargins(50, 50, 50, 50);
    QRectF plotArea;
    QBrush brushBackground = Qt::NoBrush;
    QBrush brushPlotArea = Qt::NoBrush;
    bool square = false;
    bool halfSide = false;
    bool drawFrame = true;
    bool drawRuler = true;
    bool drawGrid = true;
    QColor colorFrame = Qt::black;
    QColor colorRuler = Qt::black;
    QColor colorGrid = QColor(128, 128, 128, 128);
    QHash<int, QColor> polygonColors;
    QHash<int, QPolygonF> polygons;
};

#endif // HDIAGRAMWIDGET_P_H
