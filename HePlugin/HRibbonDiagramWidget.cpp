#include "HRibbonDiagramWidget_p.h"
#include "HCartesianCoordinate.h"
#include "HeAlgorithm/HMath.h"
#include <QPainter>

HE_ALGORITHM_USE_NAMESPACE

HRibbonDiagramWidgetPrivate::HRibbonDiagramWidgetPrivate(HRibbonDiagramWidget *q)
    : HCartesianWidgetPrivate(q)
{
    pixmapRibbon.load(":/image/7color.png");
}

HRibbonDiagramWidget::HRibbonDiagramWidget(QWidget *parent)
    : HCartesianWidget(*new HRibbonDiagramWidgetPrivate(this), parent)
{
}

HRibbonDiagramWidget::HRibbonDiagramWidget(HRibbonDiagramWidgetPrivate &p, QWidget *parent)
    : HCartesianWidget(p, parent)
{
}

HRibbonDiagramWidget::~HRibbonDiagramWidget()
{
}

void HRibbonDiagramWidget::setPolygonRibbon(QPolygonF value)
{
    Q_D(HRibbonDiagramWidget);
    d->polyRibbon = value;
    refreshPixmap();
}

bool HRibbonDiagramWidget::drawElse(QPainter *painter)
{
    HCartesianWidget::drawElse(painter);
    return drawRibbon(painter);
}

bool HRibbonDiagramWidget::drawRibbon(QPainter *painter)
{
    Q_D(HRibbonDiagramWidget);
    if (!d->plotArea.isValid())
        return false;

    QColor color;
    if (d->brushPlotArea != Qt::NoBrush)
        color = d->brushPlotArea.color();
    else if (d->brushBackground.style() != Qt::NoBrush)
        color = d->brushBackground.color();
    else
        color = palette().background().color();

    auto target = d->plotArea.adjusted(1, 1, -1, -1);
    auto source = d->coordinate->mapToAxis(d->pixmapRibbon.rect(), QRectF(360, 0, 470, 100));
    auto poly = d->coordinate->mapToPosition(d->polyRibbon, d->plotArea);
    poly = HMath::interpolate(poly, d->plotArea.left(), d->plotArea.right(), d->plotArea.bottom(), 1);

    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->drawPixmap(target, d->pixmapRibbon, source);
    painter->setPen(color);
    for (auto p : poly)
        painter->drawLine(p.x(), d->plotArea.top(), p.x(), p.y());
    painter->restore();
    return true;
}

void HRibbonDiagramWidget::init()
{
    auto coordinate = new HCartesianCoordinate(this);
    coordinate->setAxis(QRectF(380, 0, 400, 100), 5, 5);
    setCoordinate(coordinate);
}
