#include "HCartesianZoom_p.h"
#include "HCartesianCoordinate.h"
#include "HRubberBand.h"
#include <QtWidgets/QToolButton>

HCartesianZoomPrivate::HCartesianZoomPrivate(QWidget *p) :
    HAbstractMouseStrategyPrivate(p)
{
    zoomIn = new QToolButton(p);
    zoomIn->setIcon(QIcon(":/image/ZoomIn.png"));
    zoomIn->adjustSize();
    zoomOut = new QToolButton(p);
    zoomOut->setIcon(QIcon(":/image/ZoomOut.png"));
    zoomOut->adjustSize();
    rubberBand = new HRubberBand(p);
}

HCartesianZoom::HCartesianZoom(QWidget *parent) :
    HAbstractMouseStrategy(*new HCartesianZoomPrivate(parent), parent)
{
    init();
}

HCartesianZoom::HCartesianZoom(HCartesianZoomPrivate &p, QWidget *parent) :
    HAbstractMouseStrategy(p, parent)
{
    init();
}

void HCartesianZoom::setCoordinate(HCartesianCoordinate *p)
{
    Q_D(HCartesianZoom);
    d->coordinates.clear();
    d->coordinates.append(p);
    d->pos = 0;
    zoom();
}

void HCartesianZoom::resetCoordinate()
{
    Q_D(HCartesianZoom);
    setCoordinate(d->coordinates.first());
}

bool HCartesianZoom::setValidRegion(QRectF value)
{
    Q_D(HCartesianZoom);
    if (!HAbstractMouseStrategy::setValidRegion(value))
        return false;
    d->rubberBand->setValidRegion(value);
    d->zoomIn->move(value.right() - 1 - d->zoomIn->width() - d->zoomOut->width(), value.top() + 1);
    d->zoomOut->move(value.right() - 1 - d->zoomOut->width(), value.top() + 1);
    return true;
}

bool HCartesianZoom::mousePressEvent(QMouseEvent *event)
{
    Q_D(HCartesianZoom);
    if (!isEnable())
        return false;
    return d->rubberBand->mousePressEvent(event);
}

bool HCartesianZoom::mouseMoveEvent(QMouseEvent *event)
{
    Q_D(HCartesianZoom);
    if (!isEnable())
        return false;
    return d->rubberBand->mouseMoveEvent(event);
}

bool HCartesianZoom::mouseReleaseEvent(QMouseEvent *event)
{
    Q_D(HCartesianZoom);
    if (!isEnable())
        return false;
    return d->rubberBand->mouseReleaseEvent(event);
}

void HCartesianZoom::handleRubberBandChanged(QRectF value)
{
    Q_D(HCartesianZoom);
    auto first = d->coordinates.first();
    auto rect = d->coordinates[d->pos]->mapToValue(value, d->validRegion);
    auto coordinate = new HCartesianCoordinate(this);
    coordinate->setAxis(rect);
    if (first->spanX() / coordinate->spanX() > 1000 || first->spanY() / coordinate->spanY() > 1000)
        return;
    d->coordinates.resize(d->pos + 1);
    d->coordinates.append(coordinate);
    zoomIn();
}

void HCartesianZoom::zoomIn()
{
    Q_D(HCartesianZoom);
    if (d->pos >= d->coordinates.count() - 1)
        return;
    d->pos++;
    zoom();
}

void HCartesianZoom::zoomOut()
{
    Q_D(HCartesianZoom);
    if (d->pos <= 0)
        return;
    d->pos--;
    zoom();
}

void HCartesianZoom::zoom()
{
    Q_D(HCartesianZoom);
    d->zoomIn->setVisible(d->pos > 0 && d->pos < d->coordinates.count() - 1);
    d->zoomOut->setVisible(d->pos > 0);
    emit coordinateChanged(d->coordinates[d->pos]);
}

void HCartesianZoom::init()
{
    Q_D(HCartesianZoom);
    connect(d->rubberBand, &HRubberBand::rubberBandChanged, this, &HCartesianZoom::handleRubberBandChanged);
    connect(d->zoomIn, &QToolButton::clicked, this, &HCartesianZoom::zoomIn);
    connect(d->zoomOut, &QToolButton::clicked, this, &HCartesianZoom::zoomOut);
}
