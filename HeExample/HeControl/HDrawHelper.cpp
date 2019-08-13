#include "HDrawHelper.h"
#include <QtGui/QPainter>
#include <QtGui/QImage>

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

QImage HDrawHelper::createTiledImage(QColor color1, QColor color2, int size)
{
    auto image = QImage(size * 2, size * 2, QImage::Format_ARGB32);
    image.fill(color1);

    QPainter painter(&image);
    painter.fillRect(0, 0, size, size, color2);
    painter.fillRect(size, size, size, size, color2);
    return image;
}

QImage HDrawHelper::createCrossImage(QSize size, QPen pen)
{
    QPainterPath path;
    path.moveTo(0, size.height() / 2);
    path.lineTo(size.width(), size.height() / 2);
    path.moveTo(size.width() / 2, 0);
    path.lineTo(size.width() / 2, size.height());

    auto image = QImage(size, QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawPath(path);
    return image;
}

HE_CONTROL_END_NAMESPACE
