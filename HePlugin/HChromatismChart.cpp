#include "HChromatismChart_p.h"
#include "HDrawHelper.h"
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>

HChromatismChartPrivate::HChromatismChartPrivate()
{
    ellipse = new QLineSeries;
    focus = new QScatterSeries;
    focus->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    focus->setMarkerSize(11.0);
    focus->setPen(QColor(Qt::transparent));
    focus->setBrush(HDrawHelper::createCrossImage(QSize(9, 9), QPen(Qt::red, 2)));
    focus->append(0.5, 0.5);
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

void HChromatismChart::setEllipse(const QPolygonF &value)
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

void HChromatismChart::setAxesXTitle(const QString &value)
{
    axes(Qt::Horizontal).at(0)->setTitleText(value);
}

void HChromatismChart::createFixAxes()
{
    Q_D(HChromatismChart);
    auto x1 = d->center->at(0).x();
    auto x2 = d->center->at(0).x();
    auto y1 = d->center->at(0).y();
    auto y2 = d->center->at(0).y();
    for (auto p : d->ellipse->points())
    {
        x1 = qMin(x1, p.x());
        x2 = qMax(x2, p.x());
        y1 = qMin(y1, p.y());
        y2 = qMax(y2, p.y());
    }
    x1 = int((x1 - 0.005) * 500) / 500.0;
    x2 = int((x2 + 0.005) * 500) / 500.0;
    y1 = int((y1 - 0.005) * 500) / 500.0;
    y2 = int((y2 + 0.005) * 500) / 500.0;

    auto axisX = new QValueAxis;
    axisX->setRange(x1, x2);
    axisX->setTickCount(6);
    axisX->setTitleFont(titleFont());
    setAxisX(axisX);
    auto axisY = new QValueAxis;
    axisY->setRange(y1, y2);
    axisY->setTickCount(6);
    setAxisY(axisY);

    for (auto s : series())
    {
        s->attachAxis(axisX);
        s->attachAxis(axisY);
    }
}

void HChromatismChart::init()
{
    Q_D(HChromatismChart);
    auto f = font();
    f.setPixelSize(15);
    f.setBold(true);
    setTitleFont(f);
    addSeries(d->ellipse);
    addSeries(d->focus);
    addSeries(d->center);
    createFixAxes();
    legend()->hide();
    setMinimumSize(300, 300);
}
