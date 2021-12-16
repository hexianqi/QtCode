#include "HRibbonDiagramWidget_p.h"
#include "HCartesianCoordinate.h"
#include "HeAlgorithm/HInterp.h"
#include "HeAlgorithm/HMath.h"
#include "HeAlgorithm/HSpecHelper.h"
#include <QtGui/QPainter>
#include <QtWidgets/QAction>
#include <QDebug>
#include <QTime>

HE_USE_NAMESPACE

HRibbonDiagramWidgetPrivate::HRibbonDiagramWidgetPrivate()
{
    pixmapRibbon.load(":/image/7color.png");
}

HRibbonDiagramWidget::HRibbonDiagramWidget(QWidget *parent) :
    HCartesianWidget(*new HRibbonDiagramWidgetPrivate, parent)
{
    init();
}

HRibbonDiagramWidget::HRibbonDiagramWidget(HRibbonDiagramWidgetPrivate &p, QWidget *parent) :
    HCartesianWidget(p, parent)
{
    init();
}

void HRibbonDiagramWidget::setDrawRibbon(bool b)
{
    Q_D(HRibbonDiagramWidget);
    if (d->drawRibbon == b)
        return;
    d->drawRibbon = b;
    d->actionRibbon->setChecked(b);
    refreshPixmap();
}

void HRibbonDiagramWidget::setPolygonRibbon(const QPolygonF &value, bool refresh)
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
    if (!isDrawRibbon() || !isValid() || d->polyRibbon.count() < 1)
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
    poly = HMath::interpolate(poly, d->plotArea.left(), d->plotArea.right(), 1);
//    poly = HInterp::eval(poly, d->plotArea.left(), d->plotArea.right(), 1, HInterpType::Cspline);

    painter->save();
    painter->setClipRect(d->plotArea.adjusted(+1, +1, -1, -1));
    painter->drawPixmap(target, d->pixmapRibbon, source);
    painter->setPen(color);
    for (auto p : poly)
        painter->drawLine(p.x(), d->plotArea.top(), p.x(), p.y());
    //    painter->drawLine(QLineF(p.x(), d->plotArea.top(), p.x(), p.y())); 会死机
    painter->restore();
    return true;
}

void HRibbonDiagramWidget::init()
{
    Q_D(HRibbonDiagramWidget);
    d->actionRibbon = new QAction(tr("颜色图"));
    d->actionRibbon->setCheckable(true);
    d->actionRibbon->setChecked(isDrawRibbon());
    addAction(d->actionRibbon);
    connect(d->actionRibbon, &QAction::toggled, this, &HRibbonDiagramWidget::setDrawRibbon);
    setCoordinate(QRectF(380, 0, 400, 100), 5, 5);
}
