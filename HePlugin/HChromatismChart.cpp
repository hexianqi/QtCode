#include "HChromatismChart_p.h"
#include "HPluginHelper.h"
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>

HChromatismChartPrivate::HChromatismChartPrivate()
{
    ellipse = new QLineSeries;
    focus = new QScatterSeries;
    focus->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    focus->setMarkerSize(11.0);
    focus->setPen(QColor(Qt::transparent));
    focus->setBrush(HPluginHelper::createCrossImage(QSize(9, 9), QPen(Qt::red, 2)));
    focus->append(0.0, 0.0);
    center = new QScatterSeries();
    center->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    center->setMarkerSize(10.0);
    center->append(0.5, 0.5);
}

HChromatismChart::HChromatismChart(QGraphicsItem *parent, Qt::WindowFlags wFlags) :
    HChart(*new HChromatismChartPrivate, parent, wFlags)
{
    init();
}

HChromatismChart::~HChromatismChart()
{
}

void HChromatismChart::setEllipse(QPolygonF value)
{
    Q_D(HChromatismChart);
    d->ellipse->replace(value);
}

void HChromatismChart::setPointFocus(QPointF value)
{
    Q_D(HChromatismChart);
    d->focus->replace(0, value);
}

void HChromatismChart::setPointCenter(QPointF value)
{
    Q_D(HChromatismChart);
    d->center->replace(0, value);
}

void HChromatismChart::setAxesXTitle(QString value)
{
    auto ax = axes(Qt::Horizontal).at(0);
    QFont font;
    font.setPixelSize(15);
    font.setBold(true);
    ax->setTitleFont(font);
    ax->setTitleText(value);
}

void HChromatismChart::init()
{
    Q_D(HChromatismChart);
    QFont font;
    font.setPixelSize(15);
    font.setBold(true);
    setTitleFont(font);
    addSeries(d->ellipse);
    addSeries(d->focus);
    addSeries(d->center);
    legend()->hide();
    setMinimumSize(300, 300);
}
