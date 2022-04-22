#include "HPainterHelper.h"
#include <QtGui/QPainter>
#include <QtWidgets/QWidget>

QPointF HPainterHelper::drawText(QPainter *painter, double x, double y, const QString &text, int flags)
{
    return drawText(painter, QRectF(x, y, painter->viewport().width() - x, painter->viewport().height() - y), text, flags);
}

QPointF HPainterHelper::drawText(QPainter *painter, QRectF rect, const QString &text, int flags)
{
    rect = painter->boundingRect(rect, flags, text);
    painter->drawText(rect, flags, text);
    return rect.bottomRight();
}

QPointF HPainterHelper::drawLogo(QPainter *painter, QRectF rect, QString fileName)
{
    if (fileName.isEmpty())
        fileName = ":/image/Logo.png";
    QPixmap pixmap(fileName);
    painter->drawPixmap(rect, pixmap, pixmap.rect());
    return rect.bottomRight();
}

QPointF HPainterHelper::drawChart(QPainter *painter, QRectF rect, QWidget *widget)
{
    if (!widget->windowTitle().isEmpty())
    {
        auto p = drawText(painter, rect, widget->windowTitle(), Qt::AlignHCenter);
        rect.setTop(p.y());
    }
 //   auto side = qMin(rect.width(), rect.height());
 //   rect.adjust((rect.width() - side) / 2, 0, -(rect.width() - side) / 2, -(rect.height() - side));
    widget->resize(rect.size().toSize());
    widget->render(painter, rect.topLeft().toPoint());
    return rect.bottomRight();
}

void HPainterHelper::drawQuiver(QPainter *painter, QPointF p1, QPointF p2, int size)
{
    QLineF line1, line2, line3;
    line1.setP1(p1);
    line1.setP2(p2);
    line2.setP1(p2);
    line2.setLength(size);
    line2.setAngle(line1.angle() + 20 + 180);
    line3.setP1(p2);
    line3.setLength(size);
    line3.setAngle(line1.angle() - 20 + 180);
    painter->drawLine(line1);
    painter->drawLine(line2);
    painter->drawLine(line3);
}

void HPainterHelper::drawCrosshair(QPainter *painter, QPointF point, int size, const QColor &color)
{
    painter->save();
    painter->setPen(QPen(color, size));
    painter->drawLine(point - QPointF(0, -size * 3),  point - QPointF(0, -size));
    painter->drawLine(point - QPointF(0,  size * 3),  point - QPointF(0,  size));
    painter->drawLine(point - QPointF(-size * 3, 0),  point - QPointF(-size, 0));
    painter->drawLine(point - QPointF( size * 3, 0),  point - QPointF( size, 0));
    painter->restore();
}

void HPainterHelper::drawCrossCursor(QPainter *painter, QPointF point, int size, const QColor &color)
{
    auto text = QString("+");
    auto font = painter->font();
    font.setPixelSize(size);
    auto fm = QFontMetrics(font);
    QPainterPath path;
    path.addText(point - QPointF(fm.width(text) / 2.0, -fm.height() / 4.0), font, text);

    painter->save();
    painter->setPen(color);
    painter->drawPath(path);
    painter->restore();
}

void HPainterHelper::drawCrossCursor(QPainter *painter, QPointF point, int size)
{
    painter->drawLine(QLineF(point.x(), point.y() - size, point.x(), point.y() + size));
    painter->drawLine(QLineF(point.x() - size, point.y(), point.x() + size, point.y()));
}

double HPainterHelper::paintHeader(QPainter *painter, const QVariantMap &param)
{
    if (param.value("DrawHeader", true).toBool())
        HPainterHelper::drawText(painter, 20, 5, param.value("Header").toString());
    if (param.value("DrawLogo", true).toBool())
        HPainterHelper::drawLogo(painter, QRectF(painter->viewport().width() - 180, 0, 162, 30), param.value("LogoFile").toString());
    painter->drawLine(0, 35, painter->viewport().width(), 35);
    return 50;
}

double HPainterHelper::paintFooter(QPainter *painter, const QString &text)
{
    auto y = painter->viewport().height() - painter->fontMetrics().lineSpacing() - 10;
    painter->drawLine(0, y, painter->viewport().width(), y);
    drawText(painter, 0, y, text, Qt::AlignCenter);
    return y - 5;
}

double HPainterHelper::paintTitle(QPainter *painter, const QString &text, double y)
{
    return drawText(painter, 0, y, text, Qt::AlignHCenter | Qt::TextWordWrap).y() + 10;
}
