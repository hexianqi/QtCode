#pragma once

#include "HLedWidget.h"

HE_CONTROL_BEGIN_NAMESPACE

class HLedWidgetPrivate
{
public:
    QColor color = Qt::red;
    bool checked = false;
    HLedWidget::ShapeStyle shapeStyle = HLedWidget::ShapeStyle_Circular;
    int frameWidth = 1;
    QTimer *timer = nullptr;
};

HE_CONTROL_END_NAMESPACE
