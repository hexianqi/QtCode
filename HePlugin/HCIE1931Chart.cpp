#include "HCIE1931Chart_p.h"
#include <QTextStream>
#include <QLineSeries>
#include <QAreaSeries>
#include <QScatterSeries>
#include <QPainter>

HCIE1931ChartPrivate::HCIE1931ChartPrivate()
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
    : QChart(QChart::ChartTypeCartesian, parent, wFlags), d_ptr(new HCIE1931ChartPrivate)
{
    initSeries();
    initAxes();
    initLegend();
    connect(this, &HCIE1931Chart::plotAreaChanged, this, &HCIE1931Chart::updateHorseshoeBrush);

    //    QValueAxis *axisX = new QValueAxis;
    //    axisX->setRange(0, 0.75);
    //    axisX->setTickCount(6);
    //    setAxisX(axisX);

    //    QValueAxis *axisY = new QValueAxis;
    //    axisY->setRange(0, 0.85);
    //    axisY->setTickCount(6);
    //    setAxisY(axisY);

    //    d_ptr->horseshoe = new QLineSeries;
    //    d_ptr->planckian = new QLineSeries;
    //    readStandard();
    //    addSeries(d_ptr->horseshoe);
    //    addSeries(d_ptr->planckian);
    //    d_ptr->horseshoe->attachAxis(axisX);
    //    d_ptr->horseshoe->attachAxis(axisY);
    //    d_ptr->planckian->attachAxis(axisX);
    //    d_ptr->planckian->attachAxis(axisY);
}

HCIE1931Chart::~HCIE1931Chart()
{
}

void HCIE1931Chart::setEnableCIE(bool b)
{
    if (d_ptr->enableCIE == b)
        return;

    d_ptr->enableCIE = b;
    if (b)
        updateHorseshoeBrush();
    else
        d_ptr->horseshoe->setBrush(Qt::NoBrush);
}

void HCIE1931Chart::setEnableHorseshoe(bool b)
{
    if (d_ptr->enableHorseshoe == b)
        return;
    d_ptr->enableHorseshoe = b;
    if (b)
        d_ptr->horseshoe->setPen(QPen(Qt::black));
    else
        d_ptr->horseshoe->setPen(Qt::NoPen);
}

void HCIE1931Chart::setEnablePlanckian(bool b)
{
    if (d_ptr->enablePlanckian == b)
        return;
    d_ptr->enablePlanckian = b;
    d_ptr->planckian->setVisible(b);
}

void HCIE1931Chart::setEnableGrade(bool b)
{
    if (d_ptr->enableGrade == b)
        return;
    d_ptr->enableGrade = b;
    d_ptr->gradeFocus->setVisible(b);
    for (auto s : d_ptr->grades)
        s->setVisible(b);
}

void HCIE1931Chart::setEnablePoint(bool b)
{
    if (d_ptr->enablePoint == b)
        return;
    d_ptr->enablePoint = b;
    d_ptr->pointFocus->setVisible(b);
    d_ptr->points->setVisible(b);
}

bool HCIE1931Chart::isEnableCIE()
{
    return d_ptr->enableCIE;
}

bool HCIE1931Chart::isEnableHorseshoe()
{
    return d_ptr->enableHorseshoe;
}

bool HCIE1931Chart::isEnablePlanckian()
{
    return d_ptr->enablePlanckian;
}

bool HCIE1931Chart::isEnableGrade()
{
    return d_ptr->enableGrade;
}

bool HCIE1931Chart::isEnablePoint()
{
    return d_ptr->enablePoint;
}

void HCIE1931Chart::setGradeFocus(QPolygonF value)
{
    d_ptr->gradeFocus->clear();
    d_ptr->gradeFocus->append(value.toList());
    d_ptr->gradeFocus->append(value.first());
}

void HCIE1931Chart::setGrades(QList<QPolygonF> value)
{
    clearGrade();
    for (auto poly : value)
        addGrade(poly, false);
}

void HCIE1931Chart::addGrade(QPolygonF value, bool focus)
{
    auto series = new QLineSeries;
    series->setColor(Qt::black);
    series->append(value.toList());
    series->append(value.first());
    addSeries(series);
    d_ptr->grades << series;
    if (focus)
        setGradeFocus(value);
}

void HCIE1931Chart::clearGrade()
{
    d_ptr->gradeFocus->clear();
    for (auto s : d_ptr->grades)
        removeSeries(s);
    qDeleteAll(d_ptr->grades);
    d_ptr->grades.clear();
}

void HCIE1931Chart::setPointFocus(QPointF value)
{
    d_ptr->pointFocus->clear();
    d_ptr->pointFocus->append(value);
}

void HCIE1931Chart::setPoints(QList<QPointF> value)
{
    clearPoint();
    d_ptr->points->append(value);
}

void HCIE1931Chart::addPoint(QPointF value, bool focus)
{
    d_ptr->points->append(value);
    if (focus)
        setPointFocus(value);
}

void HCIE1931Chart::clearPoint()
{
    d_ptr->pointFocus->clear();
    d_ptr->points->clear();
}

void HCIE1931Chart::initSeries()
{
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
    d_ptr->horseshoe->setUpperSeries(series0);
    d_ptr->horseshoe->setLowerSeries(series1);

    in >> str >> n;
    for (i = 0; i < n; i++)
    {
        in >> x >> y;
        d_ptr->planckian->append(x, y);
    }
    addSeries(d_ptr->horseshoe);
    addSeries(d_ptr->planckian);
    addSeries(d_ptr->pointFocus);
    addSeries(d_ptr->points);
    addSeries(d_ptr->gradeFocus);

    addGrade(QPolygonF() << QPointF(0.1, 0.3) << QPointF(0.2, 0.2) << QPointF(0.5, 0.5));
    addPoint(QPointF(0.4, 0.4));
}

void HCIE1931Chart::initAxes()
{
    createDefaultAxes();
    axisX()->setRange(0.0, 0.75);
    axisY()->setRange(0.0, 0.85);
}

void HCIE1931Chart::initLegend()
{
    legend()->hide();
}

void HCIE1931Chart::updateHorseshoeBrush()
{
    if (!isEnableCIE())
        return;

    QBrush br;
    QTransform tran;

    auto rect = plotArea();
    auto p1 = mapToValue(rect.bottomLeft());
    auto p2 = mapToValue(rect.topRight());
    tran.scale(rect.width() / d_ptr->cie.width() / (p2.x() - p1.x()), rect.height() / d_ptr->cie.height() / (p2.y() - p1.y()));
    tran.translate(-p1.x() * d_ptr->cie.width(), (p2.y() - 1) * d_ptr->cie.height());

    br.setTexture(d_ptr->cie);
    br.setTransform(tran);
    d_ptr->horseshoe->setBrush(br);
}
