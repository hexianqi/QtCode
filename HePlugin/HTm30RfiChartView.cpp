#include "HTm30RfiChartView_p.h"
#include "HTm30BarChart.h"
#include <QtCore/QTextStream>
#include <QtCharts/QBarSeries>

HTm30RfiChartView::HTm30RfiChartView(QWidget *parent) :
    HZoomChartView(*new HTm30RfiChartViewPrivate, nullptr, parent)
{
    init();
}

HTm30RfiChartView::~HTm30RfiChartView()
{
}

HTm30BarChart *HTm30RfiChartView::chart()
{
    Q_D(HTm30RfiChartView);
    return d->chart;
}

void HTm30RfiChartView::init()
{
    Q_D(HTm30RfiChartView);
    readColor();
    d->chart = new HTm30BarChart(99);
    d->chart->axisY()->setTitleText("<p>Color Sample Fidelity (R<span style='vertical-align:sub;'>f,CESi</span>)</p>");
    d->chart->series()->setLabelsVisible(false);
    d->chart->setBarColor(d->color);
    setChart(d->chart);
    HZoomChartView::init();
}

void HTm30RfiChartView::readColor()
{
    Q_D(HTm30RfiChartView);
    int i,n;
    double r,g,b;
    QString str;

    QFile file(":/dat/Tm30BarCamp99.dat");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    in >> str >> n;
    for (i = 0; i < n; i++)
    {
        in >> r >> g >> b;
        d->color << QColor::fromRgbF(r, g, b);
    }
    file.close();
}


