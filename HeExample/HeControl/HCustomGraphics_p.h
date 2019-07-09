#ifndef HCUSTOMGRAPHICS_P_H
#define HCUSTOMGRAPHICS_P_H

#include "HCustomGraphics.h"

HE_CONTROL_BEGIN_NAMESPACE

class HCustomGraphicsPrivate
{
public:
    bool selectDotVisible = true;
    int dotRadius = 4;
    int lineWidth = 2;
    QColor dotColor = QColor(14, 153, 160);
    QColor lineColor = QColor(34, 163, 169);
    QColor polygonColor = QColor(162, 121, 197);
    QColor selectColor = QColor(214, 77, 84);

public:
    bool pressed = false;                   // 鼠标是否按下
    QPoint lastPoint;                       // 鼠标按下处的坐标
    QPoint tempPoint;                       // 临时点
    QList<QPoint> tempPoints;               // 临时点集合
    QPoint selectedPoint;                   // 保存按下点的坐标
    int selectedPointIndex = -1;            // 选中点的index
    int selectedIndex = -1;                 // 选中多边形的index
    QPair<QPolygon, bool> selectedPolygon;  // 保存按下时多边形的原始坐标
    QList<QPair<QPolygon, bool>> polygons;  // 多边形集合
};

HE_CONTROL_END_NAMESPACE

#endif // HCUSTOMGRAPHICS_P_H
