#include "HCartesianWidget_p.h"
#include "HCartesianZoom.h"
#include "HCartesianCoordinate.h"
#include <QMouseEvent>
#include <QPainter>
#include <QAction>

HCartesianWidgetPrivate::HCartesianWidgetPrivate(HCartesianWidget *q)
    : HDiagramWidgetPrivate(q)
{
}

HCartesianWidget::HCartesianWidget(QWidget *parent)
    : HDiagramWidget(*new HCartesianWidgetPrivate(this), parent)
{
    init();
}

HCartesianWidget::HCartesianWidget(HCartesianWidgetPrivate &p, QWidget *parent)
    : HDiagramWidget(p, parent)
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
    QString str;
    QStringList list;

    painter->save();
    painter->setPen(d->colorRuler);

    margin = d->halfSide ? 10.0 : 5.0;
    width = 1.0 * d->plotArea.width() / d->coordinate->tickX();
    height = d->margins.bottom() - 2 * margin;
    list = d->coordinate->axisX();
    for (i = 0; i < list.size(); i++)
    {
        str = list[i];
        if (d->unitInRuler)
            str += d->unitX;
        painter->drawText(d->plotArea.left() + (i - 0.5) * width, d->plotArea.bottom() + margin, width, height, Qt::AlignHCenter | Qt::AlignTop, str);
    }

    width = d->plotArea.left() - 2 * margin;
    height = 1.0 * d->plotArea.height() / d->coordinate->tickY();
    list = d->coordinate->axisY();
    for (i = 0; i < list.size(); i++)
    {
        str = list[i];
        if (d->unitInRuler)
            str += d->unitY;
        painter->drawText(margin, d->plotArea.bottom() - (i + 0.5) * height, width, height, Qt::AlignRight | Qt::AlignVCenter, str);
    }

    if (!d->unitInRuler)
    {
        painter->drawText(d->plotArea.right() + 5, d->plotArea.bottom() - 20, d->margins.right() - 10, 30, Qt::AlignVCenter | Qt::AlignLeft, d->unitX);
        painter->drawText(d->plotArea.left() - 15, 5, 30, d->plotArea.top() - 10, Qt::AlignHCenter | Qt::AlignBottom, d->unitY);
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
    QPen pen;

    painter->save();
    painter->setClipRect(d->plotArea.adjusted(-5, -5, +5, +5));
    painter->setBrush(Qt::NoBrush);
    auto tickX = d->coordinate->tickX();
    auto tickY = d->coordinate->tickY();

    if (d->halfSide)
    {
        pen.setColor(d->colorFrame);
        painter->setPen(pen);
        for (i = 0; i <= tickX; i++)
        {
            t = d->plotArea.left() + i * d->plotArea.width() / tickX;
            painter->drawLine(t, d->plotArea.bottom(), t, d->plotArea.bottom() + 5);
        }
        for (i = 0; i <= tickY; i++)
        {
            t = d->plotArea.bottom() - i * d->plotArea.height() / tickY;
            painter->drawLine(d->plotArea.left(), t, d->plotArea.left() - 5, t);
        }
    }
    else
    {
        pen.setColor(d->colorGrid);
        pen.setStyle(Qt::DashLine);
        painter->setPen(pen);
        for (i = 1; i < tickX; i++)
        {
            t = d->plotArea.left() + i * d->plotArea.width() / tickX;
            painter->drawLine(t, d->plotArea.top(), t, d->plotArea.bottom());
        }
        for (i = 1; i < tickY; i++)
        {
            t = d->plotArea.bottom() - i * d->plotArea.height() / tickY;
            painter->drawLine(d->plotArea.left(), t, d->plotArea.right(), t);
        }
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
    d->actionResetCoordinate = new QAction(this);
    d->actionResetCoordinate->setText(tr("还原(&R)"));
    connect(this, &HCartesianWidget::plotAreaChanged, d->zoom, &HCartesianZoom::setValidRegion);
    connect(d->zoom, &HCartesianZoom::coordinateChanged, this, &HCartesianWidget::handleCoordinateChanged);
    connect(d->actionResetCoordinate, &QAction::triggered, d->zoom, &HCartesianZoom::resetCoordinate);
    addAction(d->actionResetCoordinate);
    setCoordinate(new HCartesianCoordinate(this));
}

