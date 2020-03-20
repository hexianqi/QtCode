#include "HDrawHelper.h"
#include <QtGui/QPainter>
#include <QtGui/QImage>

HE_CONTROL_BEGIN_NAMESPACE

void HDrawHelper::drawOverlay(QPainter *painter, double radius, QColor color)
{
    QPainterPath smallCircle, bigCircle;
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

void HDrawHelper::drawCrosshair(QPainter *painter, QPointF point, int width, const QColor &color)
{
    painter->save();
    painter->setPen(QPen(color, width));
    painter->drawLine(point - QPointF(0, -width * 3),  point - QPointF(0, -width));
    painter->drawLine(point - QPointF(0,  width * 3),  point - QPointF(0,  width));
    painter->drawLine(point - QPointF(-width * 3, 0),  point - QPointF(-width, 0));
    painter->drawLine(point - QPointF( width * 3, 0),  point - QPointF( width, 0));
    painter->restore();
}

void HDrawHelper::drawCrossCursor(QPainter *painter, QPointF point, int size, const QColor &color)
{
    auto text = QString("+");
    auto font = painter->font();
    font.setPixelSize(size);
    auto fm = QFontMetrics(font);
    QPainterPath path;
    path.addText(point - QPointF(fm.width(text) / 2, -fm.height() / 4), font, text);

    painter->save();
    painter->setPen(color);
    painter->drawPath(path);
    painter->restore();
}

QImage HDrawHelper::createTiledImage(int size, const QColor &color1, const QColor &color2)
{
    auto image = QImage(size * 2, size * 2, QImage::Format_ARGB32);
    image.fill(color1);

    QPainter painter(&image);
    painter.fillRect(0, 0, size, size, color2);
    painter.fillRect(size, size, size, size, color2);
    return image;
}

QImage HDrawHelper::createCrossImage(QSize size, const QPen &pen)
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

QImage HDrawHelper::createFontImage(const QFont &font, const QChar &c, QSize size, const QPen &pen, int flags)
{
    auto image = QImage(size, QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(pen);
    painter.setFont(font);
    painter.drawText(image.rect(), flags, c);
    return image;
}

QFont HDrawHelper::adjustFontSize(QPainter *painter, const QString &text, double width)
{
    auto font = painter->font();
    font.setPointSize(10);
    auto fm = QFontMetricsF(font);
    auto textWidth = fm.width(text);
    font.setPointSizeF(font.pointSize() * width / textWidth);
    return font;
}

HE_CONTROL_END_NAMESPACE
