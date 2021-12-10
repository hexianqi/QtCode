#include "HTm30BarChart_p.h"
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>

HTm30BarChart::HTm30BarChart(int count, QGraphicsItem *parent, Qt::WindowFlags wFlags) :
    HSingleAxisChart(*new HTm30BarChartPrivate, parent, wFlags)
{
    initBar(count);
}

HTm30BarChart::HTm30BarChart(HTm30BarChartPrivate &p, QGraphicsItem *parent, Qt::WindowFlags wFlags) :
    HSingleAxisChart(p, parent, wFlags)
{
}

HTm30BarChart::~HTm30BarChart()
{
}

QBarSeries *HTm30BarChart::series()
{
    Q_D(HTm30BarChart);
    return d->series;
}

void HTm30BarChart::setBarValue(QList<double> value)
{
    Q_D(HTm30BarChart);
    for (int i = 0; i < d->set.size() && i < value.size(); i++)
        d->set.at(i)->replace(0, value.at(i));
}

void HTm30BarChart::setBarColor(QList<QColor> value)
{
    Q_D(HTm30BarChart);
    d->color = value;
    for (int i = 0; i < d->set.size(); i++)
        d->set.at(i)->setColor(color(i));
}

void HTm30BarChart::initBar(int count)
{
    Q_D(HTm30BarChart);
    int v = 1;
    auto space = count / 50 + 1;
    auto start = -0.5 * count;
    auto end = 0.5 * count;
    auto font = QFont("Arial", 11, QFont::Bold);
    auto color = QColor(10, 10, 10);
    auto axisX = new QCategoryAxis();
    auto axisY = new QValueAxis();
    d->series = new QBarSeries();
    d->series->setBarWidth(count);
    d->series->setLabelsVisible(true);
    d->series->setLabelsPosition(QAbstractBarSeries::LabelsOutsideEnd);
    axisX->setTitleFont(font);
    axisX->setLinePenColor(color);
    axisX->setGridLineVisible(false);
    axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
    axisX->setRange(start, end);
    axisX->setStartValue(start);
    for (double s = start; s < end; s += space, v += space)
        axisX->append(QString::number(v), s + 0.5);
    axisY->setTitleFont(font);
    axisY->setLinePenColor(color);
    axisY->setGridLineVisible(false);
    axisY->setRange(0, 100);
    setAxisX(axisX);
    setAxisY(axisY);
    setAnimationOptions(QChart::NoAnimation);
    legend()->setVisible(false);
    for (int i = 0; i < count; i++)
    {
        auto set = new QBarSet(QString("%1").arg(i+1, 2, 10, QChar('0')));
        set->setLabelColor(Qt::black);
        if (space < 2)
            set->setBorderColor(color);
        set->append(i + 1);
        d->series->append(set);
        d->set << set;
    }
    addSeries(d->series);
}

QColor HTm30BarChart::color(int i)
{
    Q_D(HTm30BarChart);
    if (d->color.size() == 0)
        return QColor();
    return d->color.at(i % d->color.size());
}

// 区块实现
//void HTm30BarChart::init()
//{
//    Q_D(HTm30BarChart);
//    auto font = this->font();
//    auto axisX = new QCategoryAxis();
//    auto axisY = new QValueAxis();
//    font.setPointSize(12);
//    axisX->setTitleFont(font);
//    axisX->setGridLineVisible(false);
//    axisX->setRange(0, d->count);
//    for (int i = 1; i <= d->count; i++)
//        axisX->append(QString::number(i), i);
//    axisY->setRange(0, 100);
//    axisY->setTitleFont(font);
//    setAxisX(axisX);
//    setAxisY(axisY);
//    setAnimationOptions(QChart::NoAnimation);
//    legend()->setVisible(false);
//    for (int i = 0; i < N; i++)
//    {
//        auto series0 = new QLineSeries();
//        auto series1 = new QLineSeries();
//        *series0 << QPointF(i, 0) << QPointF(i + 1, 0);
//        *series1 << QPointF(i, i + 1) << QPointF(i + 1, i + 1);
//        auto series = new QAreaSeries(series1, series0);
//        series->setBrush(color(i));
//        addSeries(series);
//    }
//}


