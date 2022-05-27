#pragma once

#include "HSmoothCurveDemoWidget.h"

HE_BEGIN_NAMESPACE

class HSmoothCurveDemoWidgetPrivate
{
public:
    HSmoothCurveDemoWidgetPrivate();

public:
    QVector<QPointF> datas;     // 曲线上的点
    QPainterPath pathNormal;    // 正常曲线
    QPainterPath pathSmooth1;   // 平滑曲线1
    QPainterPath pathSmooth2;   // 平滑曲线2
};

HE_END_NAMESPACE
