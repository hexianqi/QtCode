#include "HDrawHelper.h"
#include <QtGui/QPainter>

QImage HDrawHelper::createCrossImage(QSize size, const QPen &pen)
{
    QPainterPath path;
    path.moveTo(0, size.height() / 2.0);
    path.lineTo(size.width(), size.height() / 2.0);
    path.moveTo(size.width() / 2.0, 0);
    path.lineTo(size.width() / 2.0, size.height());

    QImage image(size, QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawPath(path);
    return image;
}
