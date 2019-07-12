#include "HDrawHelper.h"
#include <QtGui/QPainter>

HE_CONTROL_BEGIN_NAMESPACE

void HDrawHelper::drawOverlay(QPainter *painter, double radius, QColor color)
{
    QPainterPath smallCircle;
    QPainterPath bigCircle;
    radius -= 1;
    smallCircle.addEllipse(-radius, -radius, radius * 2, radius * 2);
    radius *= 2;
    bigCircle.addEllipse(-radius, -radius + 140, radius * 2, radius * 2);
    auto gradient = QLinearGradient(0, -radius / 2, 0, 0);
    color.setAlpha(100);
    gradient.setColorAt(0.0, color);
    color.setAlpha(30);
    gradient.setColorAt(1.0, color);
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(gradient);
    painter->rotate(-20);
    painter->drawPath(smallCircle - bigCircle);
    painter->restore();
}

HE_CONTROL_END_NAMESPACE
