#include "HSpecDiagramWidget_p.h"
#include <QPainter>

HSpecDiagramWidgetPrivate::HSpecDiagramWidgetPrivate(HSpecDiagramWidget *q)
    : HCartesianWidgetPrivate(q)
{
    fontCenter.setPointSize(18);
    fontCenter.setWeight(QFont::Bold);
    fontTopLeft.setPointSize(30);
    fontTopLeft.setWeight(QFont::Bold);
    brushCenter.setColor(Qt::black);
    brushCenter.setStyle(Qt::SolidPattern);
}

HSpecDiagramWidget::HSpecDiagramWidget(QWidget *parent)
    : HCartesianWidget(*new HSpecDiagramWidgetPrivate(this), parent)
{
}

HSpecDiagramWidget::HSpecDiagramWidget(HSpecDiagramWidgetPrivate &p, QWidget *parent)
    : HCartesianWidget(p, parent)
{
}

HSpecDiagramWidget::~HSpecDiagramWidget()
{
}

void HSpecDiagramWidget::setDrawCenter(bool b)
{
    Q_D(HSpecDiagramWidget);
    if (d->drawCenter == b)
        return;
    d->drawCenter = b;
    refreshPixmap();
}

void HSpecDiagramWidget::setDrawTopLeft(bool b)
{
    Q_D(HSpecDiagramWidget);
    if (d->drawTopLeft == b)
        return;
    d->drawTopLeft = b;
    refreshPixmap();
}

void HSpecDiagramWidget::setTextCenter(QString text, bool show, bool refresh)
{
    Q_D(HSpecDiagramWidget);
    d->textCenter = text;
    d->drawCenter = show;
    if (refresh)
        refreshPixmap();
}

void HSpecDiagramWidget::setTextTopLeft(QString text, bool refresh)
{
    Q_D(HSpecDiagramWidget);
    d->textTopLeft = text;
    if (refresh)
        refreshPixmap();
}

void HSpecDiagramWidget::setColorCenter(QColor value)
{
    Q_D(HSpecDiagramWidget);
    if (d->colorCenter == value)
        return;
    d->colorCenter = value;
    refreshPixmap();
}

void HSpecDiagramWidget::setColorTopLeft(QColor value)
{
    Q_D(HSpecDiagramWidget);
    if (d->colorTopLeft == value)
        return;
    d->colorTopLeft = value;
    refreshPixmap();
}

void HSpecDiagramWidget::setFontCenter(QFont value)
{
    Q_D(HSpecDiagramWidget);
    if (d->fontCenter == value)
        return;
    d->fontCenter = value;
    refreshPixmap();
}

void HSpecDiagramWidget::setFontTopLeft(QFont value)
{
    Q_D(HSpecDiagramWidget);
    if (d->fontTopLeft == value)
        return;
    d->fontTopLeft = value;
    refreshPixmap();
}

void HSpecDiagramWidget::setBrushCenter(QBrush value)
{
    Q_D(HSpecDiagramWidget);
    if (d->brushCenter == value)
        return;
    d->brushCenter = value;
    refreshPixmap();
}

void HSpecDiagramWidget::setCenter(QString text, QColor color, QColor brush)
{
    Q_D(HSpecDiagramWidget);
    d->drawCenter = true;
    d->textCenter = text;
    d->colorCenter = color;
    d->brushCenter.setColor(brush);
    refreshPixmap();
}

bool HSpecDiagramWidget::isDrawCenter()
{
    Q_D(HSpecDiagramWidget);
    return d->drawCenter;
}

bool HSpecDiagramWidget::isDrawTopLeft()
{
    Q_D(HSpecDiagramWidget);
    return d->drawTopLeft;
}

QString HSpecDiagramWidget::textCenter()
{
    Q_D(HSpecDiagramWidget);
    return d->textCenter;
}

QString HSpecDiagramWidget::textTopLeft()
{
    Q_D(HSpecDiagramWidget);
    return d->textTopLeft;
}

QColor HSpecDiagramWidget::colorCenter()
{
    Q_D(HSpecDiagramWidget);
    return d->colorCenter;
}

QColor HSpecDiagramWidget::colorTopLeft()
{
    Q_D(HSpecDiagramWidget);
    return d->colorTopLeft;
}

QFont HSpecDiagramWidget::fontCenter()
{
    Q_D(HSpecDiagramWidget);
    return d->fontCenter;
}

QFont HSpecDiagramWidget::fontTopLeft()
{
    Q_D(HSpecDiagramWidget);
    return d->fontTopLeft;
}

QBrush HSpecDiagramWidget::brushCenter()
{
    Q_D(HSpecDiagramWidget);
    return d->brushCenter;
}

void HSpecDiagramWidget::setPolygon(int id, QPolygonF value, bool refresh)
{
    Q_D(HSpecDiagramWidget);
    d->drawCenter = false;
    HCartesianWidget::setPolygon(id, value, refresh);
}

void HSpecDiagramWidget::refreshPixmap(bool refresh)
{
    if (size().width() == 0 || size().height() == 0)
        return;

    d_ptr->pixmap = QPixmap(size());
    d_ptr->pixmap.fill(Qt::transparent);
    QPainter painter(&d_ptr->pixmap);

    initPainter(&painter);
    drawFrame(&painter);
    drawRuler(&painter);
    if (!drawCenter(&painter))
    {
        drawPolygon(&painter);
        drawElse(&painter);
        drawGrid(&painter);
        drawLeftTop(&painter);
    }

    if (refresh)
        update();
}

bool HSpecDiagramWidget::drawCenter(QPainter *painter)
{
    Q_D(HSpecDiagramWidget);
    if (!isDrawCenter() || !d->plotArea.isValid())
        return false;

    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->setBrush(d->brushCenter);
    painter->drawRect(d->plotArea);
    painter->setFont(d->fontCenter);
    painter->setPen(d->colorCenter);
    painter->drawText(d->plotArea, Qt::AlignHCenter | Qt::AlignVCenter, d->textCenter);
    painter->restore();
    return true;
}

bool HSpecDiagramWidget::drawLeftTop(QPainter *painter)
{
    Q_D(HSpecDiagramWidget);
    if (!isDrawTopLeft() || !d->plotArea.isValid())
        return false;

    painter->save();
    painter->setFont(d->fontTopLeft);
    painter->setPen(d->colorTopLeft);
    painter->drawText(d->plotArea.adjusted(10, 10, -10, -10), Qt::AlignLeft | Qt::AlignTop, d->textTopLeft);
    painter->restore();
    return true;
}
