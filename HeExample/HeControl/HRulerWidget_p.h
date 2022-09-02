#pragma once

#include "HRulerWidget.h"

HE_BEGIN_NAMESPACE

class HRulerWidgetPrivate
{
public:
    HRulerWidgetPrivate(Qt::Orientation);

public:
    Qt::Orientations orientation;
    QColor background = Qt::white;
    QColor textColor = "#FF606060";
    QColor slidingColor = "#B3D56161";
    QFont font{"微软雅黑", 16};
    int slidingPos = 0;
    int offset = 0;
};

HE_END_NAMESPACE

