#include "HRibbonDiagramWidget_p.h"
#include "HCartesianCoordinate.h"
#include "HeAlgorithm/HInterp.h"
#include <QtGui/QPainter>
#include <QtWidgets/QAction>

HE_ALGORITHM_USE_NAMESPACE

HRibbonDiagramWidgetPrivate::HRibbonDiagramWidgetPrivate(HRibbonDiagramWidget *q)
    : HCartesianWidgetPrivate(q)
{
    pixmapRibbon.load(":/image/7color.png");
}

HRibbonDiagramWidget::HRibbonDiagramWidget(QWidget *parent)
    : HCartesianWidget(*new HRibbonDiagramWidgetPrivate(this), parent)
{
    init();
}

HRibbonDiagramWidget::HRibbonDiagramWidget(HRibbonDiagramWidgetPrivate &p, QWidget *parent)
    : HCartesianWidget(p, parent)
{
    init();
}

HRibbonDiagramWidget::~HRibbonDiagramWidget()
{
}

void HRibbonDiagramWidget::setDrawRibbon(bool b)
{
    Q_D(HRibbonDiagramWidget);
    if (d->drawRibbon == b)
        return;
    d->drawRibbon = b;
    refreshPixmap();
}

void HRibbonDiagramWidget::setPolygonRibbon(QPolygonF value, bool refresh)
{
    Q_D(HRibbonDiagramWidget);
    d->polyRibbon = value;
    if (refresh)
        refreshPixmap();
}

bool HRibbonDiagramWidget::isDrawRibbon()
{
    Q_D(HRibbonDiagramWidget);
    return d->drawRibbon;
}

bool HRibbonDiagramWidget::drawElse(QPainter *painter)
{
    HCartesianWidget::drawElse(painter);
    return drawRibbon(painter);
}

bool HRibbonDiagramWidget::drawRibbon(QPainter *painter)
{
    Q_D(HRibbonDiagramWidget);
    if (!isDrawRibbon() || !d->plotArea.isValid() || d->polyRibbon.count() < 1)
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
    poly = HInterp::eval(poly, d->plotArea.left(), d->plotArea.right(), 1, HInterpType::Cspline);

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
    auto color = new QAction(tr("颜色图"));
    color->setCheckable(true);
    color->setChecked(isDrawRibbon());
    addAction(color);
    connect(color, &QAction::toggled, this, &HRibbonDiagramWidget::setDrawRibbon);
    setCoordinate(QRectF(380, 0, 400, 100), 5, 5);
}
