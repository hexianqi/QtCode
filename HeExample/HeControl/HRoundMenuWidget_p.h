#pragma once

#include "HRoundMenuWidget.h"

HE_BEGIN_NAMESPACE

class HRoundMenuWidgetPrivate
{
public:
    HRoundMenuWidget::State currentState = HRoundMenuWidget::Shrink;
    HRoundMenuWidget::State lastState = HRoundMenuWidget::Shrink;
    double length = 0;
    double radius = 0;
    int outSideRadius = 0;
    int beforeOffset = 0;
    int currentOffset = 0;
    QPainterPath arcAreaPath;
    QRect homeRect;
    QPixmap homePixmap;
    QVector<QPixmap> images;
    QVector<QRect> menuRects;
    int pressIndex = -1;
    QPoint pressPos = QPoint(0, 0);
    QTimer *timer;
};

HE_END_NAMESPACE

