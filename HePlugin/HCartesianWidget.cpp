#include "HCartesianWidget_p.h"
#include "HCartesianZoom.h"
#include "HCartesianCoordinate.h"
#include <QtGui/QMouseEvent>
#include <QtGui/QPainter>
#include <QtWidgets/QAction>

HCartesianWidgetPrivate::HCartesianWidgetPrivate(HCartesianWidget *q) :
    HDiagramWidgetPrivate(q)
{
}

HCartesianWidget::HCartesianWidget(QWidget *parent) :
    HDiagramWidget(*new HCartesianWidgetPrivate(this), parent)
{
    init();
}

HCartesianWidget::HCartesianWidget(HCartesianWidgetPrivate &p, QWidget *parent) :
    HDiagramWidget(p, parent)
{
    init();
}

HCartesianWidget::~HCartesianWidget()
{
}

void HCartesianWidget::setCoordinate(HCartesianCoordinate *p)
{
    Q_D(HCartesianWidget);
    d->coordinate = p;
    d->zoom->setCoordinate(p);
}

void HCartesianWidget::setCoordinate(QRectF rect, int tickX, int tickY)
{
    auto coordinate = new HCartesianCoordinate(this);
    coordinate->setAxis(rect, tickX, tickY);
    setCoordinate(coordinate);
}

void HCartesianWidget::setEnableZoom(bool b)
{
    Q_D(HCartesianWidget);
    d->zoom->setEnable(b);
}

void HCartesianWidget::setUnitInRuler(bool b)
{
    Q_D(HCartesianWidget);
    if (d->unitInRuler == b)
        return;
    d->unitInRuler = b;
    refreshPixmap();
}

void HCartesianWidget::setUnitX(QString value)
{
    Q_D(HCartesianWidget);
    if (d->unitX == value)
        return;
    d->unitX = value;
    refreshPixmap();
}

void HCartesianWidget::setUnitY(QString value)
{
    Q_D(HCartesianWidget);
    if (d->unitY == value)
        return;
    d->unitY = value;
    refreshPixmap();
}

bool HCartesianWidget::isEnableZoom()
{
    Q_D(HCartesianWidget);
    return d->zoom->isEnable();
}

bool HCartesianWidget::isUnitInRuler()
{
    Q_D(HCartesianWidget);
    return d->unitInRuler;
}

QString HCartesianWidget::unitX()
{
    Q_D(HCartesianWidget);
    return d->unitX;
}

QString HCartesianWidget::unitY()
{
    Q_D(HCartesianWidget);
    return d->unitY;
}

void HCartesianWidget::appendPoint(int id, QPointF value, bool refix, bool refresh)
{
    Q_D(HCartesianWidget);
    d->polygons[id].append(value);

    if (refix)
    {
        auto axis = d->coordinate->axis();
        if (!axis.contains(value))
        {
            QRectF rect;
            rect.setLeft(qMin(value.x(), axis.left()));
            rect.setRight(qMax(value.x(), axis.right()));
            rect.setTop(qMin(value.y(), axis.top()));
            rect.setBottom(qMax(value.y(), axis.bottom()));
            d->coordinate->setAxis(rect);
            refresh = true;
        }
    }
    if (refresh)
        refreshPixmap();
}

void HCartesianWidget::mousePressEvent(QMouseEvent *e)
{
    Q_D(HCartesianWidget);
    d->zoom->mousePressEvent(e);
    HDiagramWidget::mousePressEvent(e);
}

void HCartesianWidget::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(HCartesianWidget);
    d->zoom->mouseMoveEvent(e);
    HDiagramWidget::mouseMoveEvent(e);
}

void HCartesianWidget::mouseReleaseEvent(QMouseEvent *e)
{
    Q_D(HCartesianWidget);
    d->zoom->mouseReleaseEvent(e);
    HDiagramWidget::mouseReleaseEvent(e);
}

bool HCartesianWidget::drawRuler(QPainter *painter)
{
    Q_D(HCartesianWidget);
    if (!HDiagramWidget::drawRuler(painter))
        return false;

    int i;
    double margin,width,height;
    QString text;
    QStringList list;

    painter->save();
    painter->setPen(d->colorRuler);

    margin = d->halfSide ? 10.0 : 5.0;
    width = 1.0 * d->plotArea.width() / d->coordinate->tickX();
    height = d->margins.bottom() - 2 * margin;
    list = d->coordinate->axisX();
    for (i = 0; i < list.size(); i++)
    {
        text = list[i];
        if (d->unitInRuler)
            text += d->unitX;
        painter->drawText(QRectF(d->plotArea.left() + (i - 0.5) * width, d->plotArea.bottom() + margin, width, height), Qt::AlignHCenter | Qt::AlignTop, text);
    }

    width = d->plotArea.left() - 2 * margin;
    height = 1.0 * d->plotArea.height() / d->coordinate->tickY();
    list = d->coordinate->axisY();
    for (i = 0; i < list.size(); i++)
    {
        text = list[i];
        if (d->unitInRuler)
            text += d->unitY;
        painter->drawText(QRectF(margin, d->plotArea.bottom() - (i + 0.5) * height, width, height), Qt::AlignRight | Qt::AlignVCenter, text);
    }

    if (!d->unitInRuler)
    {
        painter->drawText(QRectF(d->plotArea.right() + 5, d->plotArea.bottom() - 20, d->margins.right() - 10, 30), Qt::AlignVCenter | Qt::AlignLeft, d->unitX);
        painter->drawText(QRectF(d->plotArea.left() - 15, 5, 30, d->plotArea.top() - 10), Qt::AlignHCenter | Qt::AlignBottom, d->unitY);
    }
    painter->restore();
    return true;
}

bool HCartesianWidget::drawTick(QPainter *painter)
{
    Q_D(HCartesianWidget);
    if (!HDiagramWidget::drawTick(painter))
        return false;

    int i;
    double t;
    auto tickX = d->coordinate->tickX();
    auto tickY = d->coordinate->tickY();

    painter->save();
    painter->setClipRect(d->plotArea.adjusted(-5, -5, +5, +5));
    painter->setBrush(Qt::NoBrush);
    painter->setPen(d->colorFrame);
    for (i = 0; i <= tickX; i++)
    {
        t = d->plotArea.left() + i * d->plotArea.width() / tickX;
        painter->drawLine(QLineF(t, d->plotArea.bottom(), t, d->plotArea.bottom() + 5));
    }
    for (i = 0; i <= tickY; i++)
    {
        t = d->plotArea.bottom() - i * d->plotArea.height() / tickY;
        painter->drawLine(QLineF(d->plotArea.left(), t, d->plotArea.left() - 5, t));
    }
    painter->restore();
    return true;
}

bool HCartesianWidget::drawGrid(QPainter *painter)
{
    Q_D(HCartesianWidget);
    if (!HDiagramWidget::drawGrid(painter))
        return false;

    int i;
    double t;
    auto tickX = d->coordinate->tickX();
    auto tickY = d->coordinate->tickY();

    painter->save();
    painter->setClipRect(d->plotArea.adjusted(-5, -5, +5, +5));
    painter->setBrush(Qt::NoBrush);
    painter->setPen(QPen(d->colorGrid, 1, Qt::DashLine));
    for (i = 1; i < tickX; i++)
    {
        t = d->plotArea.left() + i * d->plotArea.width() / tickX;
        painter->drawLine(QLineF(t, d->plotArea.top(), t, d->plotArea.bottom()));
    }
    for (i = 1; i < tickY; i++)
    {
        t = d->plotArea.bottom() - i * d->plotArea.height() / tickY;
        painter->drawLine(QLineF(d->plotArea.left(), t, d->plotArea.right(), t));
    }
    painter->restore();
    return true;
}

bool HCartesianWidget::drawPolygon(QPainter *painter)
{
    Q_D(HCartesianWidget);
    if (!HDiagramWidget::drawPolygon(painter))
        return false;

    QHashIterator<int, QPolygonF> i(d->polygons);
    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    while (i.hasNext())
    {
        i.next();
        painter->setPen(d->polygonColors.value(i.key(), Qt::black));
        painter->drawPolyline(d->coordinate->mapToPosition(i.value(), d->plotArea));
    }
    painter->restore();
    return true;
}

void HCartesianWidget::handleCoordinateChanged(HCartesianCoordinate *p)
{
    Q_D(HCartesianWidget);
    d->coordinate = p;
    refreshPixmap();
}

void HCartesianWidget::init()
{
    Q_D(HCartesianWidget);
    d->zoom = new HCartesianZoom(this);
    auto reset = new QAction(QIcon(":/image/Zoom.png"), tr("还原(&R)"));
    connect(this, &HCartesianWidget::plotAreaChanged, d->zoom, &HCartesianZoom::setValidRegion);
    connect(d->zoom, &HCartesianZoom::coordinateChanged, this, &HCartesianWidget::handleCoordinateChanged);
    connect(reset, &QAction::triggered, d->zoom, &HCartesianZoom::resetCoordinate);
    addAction(reset);
    setCoordinate(new HCartesianCoordinate(this));
}

