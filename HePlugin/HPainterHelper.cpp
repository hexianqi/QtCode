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
    auto y = drawText(painter, rect, widget->windowTitle(), Qt::AlignHCenter).y();
    rect.setTop(y);
    auto side = qMin(rect.width(), rect.height());
    rect.adjust((rect.width() - side) / 2, 0, -(rect.width() - side) / 2, -(rect.height() - side));
    widget->resize(rect.size().toSize());
    widget->render(painter, rect.topLeft().toPoint());
    return rect.bottomRight();
}
