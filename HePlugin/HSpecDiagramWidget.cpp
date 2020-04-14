#include "HSpecDiagramWidget_p.h"
#include "HCartesianCoordinate.h"
#include <QtGui/QIcon>
#include <QtGui/QPainter>

HSpecDiagramWidgetPrivate::HSpecDiagramWidgetPrivate()
{
    halfSide = true;
    unitInRuler = false;
    fontCenter.setPointSize(18);
    fontCenter.setWeight(QFont::Bold);
    fontTopLeft.setPointSize(30);
    fontTopLeft.setWeight(QFont::Bold);
    brushCenter.setColor(Qt::black);
    brushCenter.setStyle(Qt::SolidPattern);
}

HSpecDiagramWidget::HSpecDiagramWidget(QWidget *parent) :
    HRibbonDiagramWidget(*new HSpecDiagramWidgetPrivate, parent)
{
    init();
}

HSpecDiagramWidget::HSpecDiagramWidget(HSpecDiagramWidgetPrivate &p, QWidget *parent) :
    HRibbonDiagramWidget(p, parent)
{
    init();
}

void HSpecDiagramWidget::setWaveRange(QPointF value)
{
    setCoordinate(QRectF(value.x(), 0, value.y() - value.x(), 100), 10, 5);
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

void HSpecDiagramWidget::setTextCenter(const QString &text, bool show, bool refresh)
{
    Q_D(HSpecDiagramWidget);
    d->textCenter = text;
    d->drawCenter = show;
    if (refresh)
        refreshPixmap();
}

void HSpecDiagramWidget::setTextTopLeft(const QString &text, bool refresh)
{
    Q_D(HSpecDiagramWidget);
    d->textTopLeft = text;
    if (refresh)
        refreshPixmap();
}

void HSpecDiagramWidget::setColorCenter(const QColor &value)
{
    Q_D(HSpecDiagramWidget);
    if (d->colorCenter == value)
        return;
    d->colorCenter = value;
    refreshPixmap();
}

void HSpecDiagramWidget::setColorTopLeft(const QColor &value)
{
    Q_D(HSpecDiagramWidget);
    if (d->colorTopLeft == value)
        return;
    d->colorTopLeft = value;
    refreshPixmap();
}

void HSpecDiagramWidget::setFontCenter(const QFont &value)
{
    Q_D(HSpecDiagramWidget);
    if (d->fontCenter == value)
        return;
    d->fontCenter = value;
    refreshPixmap();
}

void HSpecDiagramWidget::setFontTopLeft(const QFont &value)
{
    Q_D(HSpecDiagramWidget);
    if (d->fontTopLeft == value)
        return;
    d->fontTopLeft = value;
    refreshPixmap();
}

void HSpecDiagramWidget::setBrushCenter(const QBrush &value)
{
    Q_D(HSpecDiagramWidget);
    if (d->brushCenter == value)
        return;
    d->brushCenter = value;
    refreshPixmap();
}

void HSpecDiagramWidget::setCenter(const QString &text, const QColor &color, const QColor &brush)
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

void HSpecDiagramWidget::addPolygon(int id, const QPolygonF &value, bool refresh)
{
    Q_D(HSpecDiagramWidget);
    d->drawCenter = false;
    if (id == 0)
        setPolygonRibbon(value, false);
    HCartesianWidget::addPolygon(id, value, refresh);
}

void HSpecDiagramWidget::refreshPixmap(bool refresh)
{
    if (size().width() * size().height() == 0)
        return;

    d_ptr->pixmap = QPixmap(size());
    d_ptr->pixmap.fill(Qt::transparent);
    QPainter painter(&d_ptr->pixmap);

    initPixmap(&painter);
    drawFrame(&painter);
    drawRuler(&painter);
    drawTick(&painter);
    if (!drawCenter(&painter))
    {
        if (!drawRibbon(&painter))
        {
            drawPolygon(&painter);
            drawGrid(&painter);
            drawLeftTop(&painter);
        }
    }

    if (refresh)
        update();

}

bool HSpecDiagramWidget::drawCenter(QPainter *painter)
{
    Q_D(HSpecDiagramWidget);
    if (!isDrawCenter() || !isValid())
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
    if (!isDrawTopLeft() || !isValid())
        return false;

    painter->save();
    painter->setFont(d->fontTopLeft);
    painter->setPen(d->colorTopLeft);
    painter->drawText(d->plotArea.adjusted(10, 10, -10, -10), Qt::AlignLeft | Qt::AlignTop, d->textTopLeft);
    painter->restore();
    return true;
}

void HSpecDiagramWidget::init()
{
    Q_D(HSpecDiagramWidget);
    d->margins.setRight(25);
    setUnitX("nm");
    setUnitY("%");
    setMinimumSize(400, 300);
    setWaveRange(QPointF(380, 780));
    setWindowIcon(QIcon(":/image/Spectrum.png"));
    setWindowTitle(tr("相对光谱能量分布"));
}
