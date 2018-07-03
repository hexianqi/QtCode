#include "HCIE1931Chart_p.h"
#include <QValueAxis>
#include <QLineSeries>
#include <QAreaSeries>
#include <QScatterSeries>
#include <QPainter>
#include <QTextStream>

HCIE1931ChartPrivate::HCIE1931ChartPrivate(HCIE1931Chart *q)
    : HSingleAxisChartPrivate(q)
{
    cie.load(":/image/CIE1931.png");
    horseshoe = new QAreaSeries;
    horseshoe->setPen(QPen(Qt::black));
    horseshoe->setBrush(Qt::NoBrush);
    planckian = new QLineSeries;
    pointFocus = new QScatterSeries;
    pointFocus->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    pointFocus->setMarkerSize(11.0);
    pointFocus->setBrush(getCrossImage(QPen(Qt::red, 2)));
    pointFocus->setPen(QColor(Qt::transparent));
    points = new QScatterSeries;
    points->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    points->setMarkerSize(11.0);
    points->setBrush(getCrossImage(QPen(Qt::black)));
    points->setPen(QColor(Qt::transparent));
    gradeFocus = new QLineSeries;
    gradeFocus->setPen(QPen(Qt::red, 2));
}

QImage HCIE1931ChartPrivate::getCrossImage(QPen pen)
{
    QPainterPath path;
    path.moveTo(0, 5);
    path.lineTo(10, 5);
    path.moveTo(5, 0);
    path.lineTo(5, 10);

    QImage image(11, 11, QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawPath(path);
    return image;
}

HCIE1931Chart::HCIE1931Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : HSingleAxisChart(*new HCIE1931ChartPrivate(this), parent, wFlags)
{
    initAxes();
    readSeries();
    legend()->hide();
    setMinimumSize(300, 300);
    connect(this, &HCIE1931Chart::plotAreaChanged, this, updateHorseshoeBrush);
}

HCIE1931Chart::~HCIE1931Chart()
{
}

void HCIE1931Chart::setEnableCIE(bool b)
{
    Q_D(HCIE1931Chart);
    if (d->enableCIE == b)
        return;
    d->enableCIE = b;
    if (!b)
        d->horseshoe->setBrush(Qt::NoBrush);
    updateHorseshoeBrush();
}

void HCIE1931Chart::setEnableHorseshoe(bool b)
{
    Q_D(HCIE1931Chart);
    if (d->enableHorseshoe == b)
        return;
    d->enableHorseshoe = b;
    d->horseshoe->setPen(b ? QPen(Qt::black) : Qt::NoPen);
}

void HCIE1931Chart::setEnablePlanckian(bool b)
{
    Q_D(HCIE1931Chart);
    if (d->enablePlanckian == b)
        return;
    d->enablePlanckian = b;
    d->planckian->setVisible(b);
}

void HCIE1931Chart::setEnableGrade(bool b)
{
    Q_D(HCIE1931Chart);
    if (d->enableGrade == b)
        return;
    d->enableGrade = b;
    d->gradeFocus->setVisible(b);
    for (auto s : d->grades)
        s->setVisible(b);
}

void HCIE1931Chart::setEnablePoint(bool b)
{
    Q_D(HCIE1931Chart);
    if (d->enablePoint == b)
        return;
    d->enablePoint = b;
    d->pointFocus->setVisible(b);
    d->points->setVisible(b);
}

bool HCIE1931Chart::isEnableCIE()
{
    Q_D(HCIE1931Chart);
    return d->enableCIE;
}

bool HCIE1931Chart::isEnableHorseshoe()
{
    Q_D(HCIE1931Chart);
    return d->enableHorseshoe;
}

bool HCIE1931Chart::isEnablePlanckian()
{
    Q_D(HCIE1931Chart);
    return d->enablePlanckian;
}

bool HCIE1931Chart::isEnableGrade()
{
    Q_D(HCIE1931Chart);
    return d->enableGrade;
}

bool HCIE1931Chart::isEnablePoint()
{
    Q_D(HCIE1931Chart);
    return d->enablePoint;
}

void HCIE1931Chart::setGradeFocus(QPolygonF value)
{
    Q_D(HCIE1931Chart);
    d->gradeFocus->clear();
    d->gradeFocus->append(value.toList());
    d->gradeFocus->append(value.first());
}

void HCIE1931Chart::setGrades(QList<QPolygonF> value)
{
    clearGrade();
    for (auto poly : value)
        addGrade(poly, false);
}

void HCIE1931Chart::addGrade(QPolygonF value, bool focus)
{
    Q_D(HCIE1931Chart);
    auto series = new QLineSeries;
    series->setPen(QPen(Qt::black));
    series->append(value.toList());
    series->append(value.first());
    addSeries(series);
    d->grades << series;
    if (focus)
        setGradeFocus(value);
}

void HCIE1931Chart::clearGrade()
{
    Q_D(HCIE1931Chart);
    d->gradeFocus->clear();
    for (auto s : d->grades)
        removeSeries(s);
    qDeleteAll(d->grades);
    d->grades.clear();
}

void HCIE1931Chart::setPointFocus(QPointF value)
{
    Q_D(HCIE1931Chart);
    d->pointFocus->clear();
    d->pointFocus->append(value);
    emit pointFocusChanged(value);
}

void HCIE1931Chart::setPoints(QList<QPointF> value)
{
    Q_D(HCIE1931Chart);
    clearPoint();
    d->points->append(value);
}

void HCIE1931Chart::addPoint(QPointF value, bool focus)
{
    Q_D(HCIE1931Chart);
    d->points->append(value);
    if (focus)
        setPointFocus(value);
}

void HCIE1931Chart::clearPoint()
{
    Q_D(HCIE1931Chart);
    d->pointFocus->clear();
    d->points->clear();
}

void HCIE1931Chart::initAxes()
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

void HCIE1931Chart::readSeries()
{
    Q_D(HCIE1931Chart);
    int i,n;
    double x,y;
    QString str;

    QFile file(":/dat/Chromaticity.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    auto series0 = new QLineSeries();
    auto series1 = new QLineSeries();
    in >> str >> n;
    for (i = 0; i < n; i++)
    {
        in >> x >> y;
        series0->append(x, y);
    }
    series1->append(series0->at(0));
    series1->append(x, y);
    d->horseshoe->setUpperSeries(series0);
    d->horseshoe->setLowerSeries(series1);

    in >> str >> n;
    for (i = 0; i < n; i++)
    {
        in >> x >> y;
        d->planckian->append(x, y);
    }
    addSeries(d->horseshoe);
    addSeries(d->planckian);
    addSeries(d->pointFocus);
    addSeries(d->points);
    addSeries(d->gradeFocus);
}

void HCIE1931Chart::updateHorseshoeBrush()
{
    Q_D(HCIE1931Chart);
    if (!isEnableCIE())
        return;

    QBrush br;
    QTransform tran;
    auto rect = plotArea();
    auto p1 = mapToValue(rect.bottomLeft());
    auto p2 = mapToValue(rect.topRight());
    tran.scale(rect.width() / d->cie.width() / (p2.x() - p1.x()), rect.height() / d->cie.height() / (p2.y() - p1.y()));
    tran.translate(-p1.x() * d->cie.width(), (p2.y() - 1) * d->cie.height());
    br.setTexture(d->cie);
    br.setTransform(tran);
    d->horseshoe->setBrush(br);
}
