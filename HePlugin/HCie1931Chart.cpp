#include "HCie1931Chart_p.h"
#include "HPluginHelper.h"
#include <QtCore/QTextStream>
#include <QtGui/QPainter>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QScatterSeries>

HCie1931ChartPrivate::HCie1931ChartPrivate()
{
    cie.load(":/image/CIE1931.png");
    horseshoe = new QAreaSeries;
    horseshoe->setPen(QPen(Qt::black));
    horseshoe->setBrush(Qt::NoBrush);
    planckian = new QLineSeries;
    pointFocus = new QScatterSeries;
    pointFocus->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    pointFocus->setMarkerSize(11.0);
    pointFocus->setBrush(HPluginHelper::createCrossImage(QSize(11, 11), QPen(Qt::red, 2)));
    pointFocus->setPen(QColor(Qt::transparent));
    point = new QScatterSeries;
    point->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    point->setMarkerSize(11.0);
    point->setBrush(HPluginHelper::createCrossImage(QSize(11, 11), QPen(Qt::black)));
    point->setPen(QColor(Qt::transparent));
    gradeFocus = new QLineSeries;
    gradeFocus->setPen(QPen(Qt::red, 2));
}

HCie1931Chart::HCie1931Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags) :
    HSingleAxisChart(*new HCie1931ChartPrivate, parent, wFlags)
{
    init();
}

HCie1931Chart::~HCie1931Chart()
{
}

void HCie1931Chart::setEnableCIE(bool b)
{
    Q_D(HCie1931Chart);
    if (d->enableCIE == b)
        return;
    d->enableCIE = b;
    if (!b)
        d->horseshoe->setBrush(Qt::NoBrush);
    updateHorseshoeBrush();
}

void HCie1931Chart::setEnableHorseshoe(bool b)
{
    Q_D(HCie1931Chart);
    if (d->enableHorseshoe == b)
        return;
    d->enableHorseshoe = b;
    d->horseshoe->setPen(b ? QPen(Qt::black) : Qt::NoPen);
}

void HCie1931Chart::setEnablePlanckian(bool b)
{
    Q_D(HCie1931Chart);
    if (d->enablePlanckian == b)
        return;
    d->enablePlanckian = b;
    d->planckian->setVisible(b);
}

void HCie1931Chart::setEnableGrade(bool b)
{
    Q_D(HCie1931Chart);
    if (d->enableGrade == b)
        return;
    d->enableGrade = b;
    d->gradeFocus->setVisible(b);
    for (auto s : d->grades)
        s->setVisible(b);
}

void HCie1931Chart::setEnablePoint(bool b)
{
    Q_D(HCie1931Chart);
    if (d->enablePoint == b)
        return;
    d->enablePoint = b;
    d->pointFocus->setVisible(b);
    d->point->setVisible(b);
}

bool HCie1931Chart::isEnableCIE()
{
    Q_D(HCie1931Chart);
    return d->enableCIE;
}

bool HCie1931Chart::isEnableHorseshoe()
{
    Q_D(HCie1931Chart);
    return d->enableHorseshoe;
}

bool HCie1931Chart::isEnablePlanckian()
{
    Q_D(HCie1931Chart);
    return d->enablePlanckian;
}

bool HCie1931Chart::isEnableGrade()
{
    Q_D(HCie1931Chart);
    return d->enableGrade;
}

bool HCie1931Chart::isEnablePoint()
{
    Q_D(HCie1931Chart);
    return d->enablePoint;
}

void HCie1931Chart::setGradeFocus(QPolygonF value)
{
    Q_D(HCie1931Chart);
    auto p = value << value.first();
    d->gradeFocus->replace(p);
}

void HCie1931Chart::setGrades(QList<QPolygonF> value)
{
    clearGrade();
    for (auto poly : value)
        addGrade(poly, false);
}

void HCie1931Chart::addGrade(QPolygonF value, bool focus)
{
    Q_D(HCie1931Chart);
    auto p = value << value.first();
    auto series = new QLineSeries;
    series->setPen(QPen(Qt::black));
    series->replace(p);
    addSeries(series);
    d->grades << series;
    if (focus)
        setGradeFocus(value);
}

void HCie1931Chart::clearGrade()
{
    Q_D(HCie1931Chart);
    d->gradeFocus->clear();
    for (auto s : d->grades)
        removeSeries(s);
    qDeleteAll(d->grades);
    d->grades.clear();
}

void HCie1931Chart::setPointFocus(QPointF value)
{
    Q_D(HCie1931Chart);
    d->pointFocus->replace(0, value);
    emit pointFocusChanged(value);
}

void HCie1931Chart::setPoints(QList<QPointF> value)
{
    Q_D(HCie1931Chart);
    d->point->replace(value);
}

void HCie1931Chart::addPoint(QPointF value, bool focus)
{
    Q_D(HCie1931Chart);
    d->point->append(value);
    if (focus)
        setPointFocus(value);
}

void HCie1931Chart::clearPoint()
{
    Q_D(HCie1931Chart);
    d->pointFocus->clear();
    d->point->clear();
}

void HCie1931Chart::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    updateHorseshoeBrush();
    HSingleAxisChart::paint(painter, option, widget);
}

void HCie1931Chart::init()
{
    initAxes();
    readSeries();
    legend()->hide();
    setMinimumSize(300, 300);
}

void HCie1931Chart::initAxes()
{
    auto axisX = new QValueAxis;
    axisX->setRange(0.0, 0.75);
    axisX->setTickCount(6);
    setAxisX(axisX);
    auto axisY = new QValueAxis;
    axisY->setRange(0.0, 0.85);
    axisY->setTickCount(6);
    setAxisY(axisY);
}

void HCie1931Chart::readSeries()
{
    Q_D(HCie1931Chart);
    int i,n;
    double x,y;
    QString str;
    QPolygonF horseshoeU, horseshoeL, planckian;

    QFile file(":/dat/Chromaticity.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    in >> str >> n;
    for (i = 0; i < n; i++)
    {
        in >> x >> y;
        horseshoeU << QPointF(x,y);
    }
    horseshoeL << horseshoeU.first() << horseshoeU.last();
    in >> str >> n;
    for (i = 0; i < n; i++)
    {
        in >> x >> y;
        planckian << QPointF(x,y);
    }

    auto series0 = new QLineSeries;
    auto series1 = new QLineSeries;
    series0->replace(horseshoeU);
    series1->replace(horseshoeL);
    d->horseshoe->setUpperSeries(series0);
    d->horseshoe->setLowerSeries(series1);
    d->planckian->replace(planckian);
    addSeries(d->horseshoe);
    addSeries(d->planckian);
    addSeries(d->pointFocus);
    addSeries(d->point);
    addSeries(d->gradeFocus);
}

void HCie1931Chart::updateHorseshoeBrush()
{
    Q_D(HCie1931Chart);
    if (!isEnableCIE())
        return;

    QBrush brush;
    QTransform tran;
    auto rect = plotArea();
    auto p1 = mapToValue(rect.bottomLeft());
    auto p2 = mapToValue(rect.topRight());
    tran.scale(rect.width() / d->cie.width() / (p2.x() - p1.x()), rect.height() / d->cie.height() / (p2.y() - p1.y()));
    tran.translate(-p1.x() * d->cie.width(), (p2.y() - 1) * d->cie.height());
    brush.setTexture(d->cie);
    brush.setTransform(tran);
    if (d->horseshoe->brush() != brush)
        d->horseshoe->setBrush(brush);
}
