#include "HCartesianZoom_p.h"
#include "HCartesianCoordinate.h"
#include "HRubberBand.h"
#include <QToolButton>

HCartesianZoomPrivate::HCartesianZoomPrivate(QWidget *p)
    : HAbstractMouseStrategyPrivate(p)
{
    zoomIn = new QToolButton(p);
    zoomIn->setIcon(QIcon(":/image/ZoomIn.png"));
    zoomIn->adjustSize();
    zoomOut = new QToolButton(p);
    zoomOut->setIcon(QIcon(":/image/ZoomOut.png"));
    zoomOut->adjustSize();
    rubberBand = new HRubberBand(p);
}

HCartesianZoom::HCartesianZoom(QWidget *parent)
    : HAbstractMouseStrategy(*new HCartesianZoomPrivate(parent), parent)
{
    init();
}

HCartesianZoom::HCartesianZoom(HCartesianZoomPrivate &p, QWidget *parent)
    : HAbstractMouseStrategy(p, parent)
{
    init();
}

HCartesianZoom::~HCartesianZoom()
{

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

void HCartesianZoom::setValidRegion(QRectF value)
{
    Q_D(HCartesianZoom);
    d->rubberBand->setValidRegion(value);
    d->zoomIn->move(value.right() - 1 - d->zoomIn->width() - d->zoomOut->width(), value.top() + 1);
    d->zoomOut->move(value.right() - 1 - d->zoomOut->width(), value.top() + 1);
    HAbstractMouseStrategy::setValidRegion(value);
}

bool HCartesianZoom::mousePressEvent(QMouseEvent *e)
{
    Q_D(HCartesianZoom);
    if (!isEnable())
        return false;
    return d->rubberBand->mousePressEvent(e);
}

bool HCartesianZoom::mouseMoveEvent(QMouseEvent *e)
{
    Q_D(HCartesianZoom);
    if (!isEnable())
        return false;
    return d->rubberBand->mouseMoveEvent(e);
}

bool HCartesianZoom::mouseReleaseEvent(QMouseEvent *e)
{
    Q_D(HCartesianZoom);
    if (!isEnable())
        return false;
    return d->rubberBand->mouseReleaseEvent(e);
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
    connect(d->rubberBand, &HRubberBand::rubberBandChanged, this, handleRubberBandChanged);
    connect(d->zoomIn, &QToolButton::clicked, this, zoomIn);
    connect(d->zoomOut, &QToolButton::clicked, this, zoomOut);
}


