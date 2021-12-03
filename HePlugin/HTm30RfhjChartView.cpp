#include "HTm30RfhjChartView_p.h"
#include "HTm30BarChart.h"
#include <QtCharts/QBarSeries>

HTm30RfhjChartView::HTm30RfhjChartView(QWidget *parent) :
    HZoomChartView(*new HTm30RfhjChartViewPrivate, nullptr, parent)
{
    init();
}

HTm30RfhjChartView::~HTm30RfhjChartView()
{
}

HTm30BarChart *HTm30RfhjChartView::chart()
{
    Q_D(HTm30RfhjChartView);
    return d->chart;
}

void HTm30RfhjChartView::init()
{
    Q_D(HTm30RfhjChartView);

    QList<QColor> color;
    color << QColor(163, 92, 96)
          << QColor(204, 118, 94)
          << QColor(204, 129, 69)
          << QColor(216, 172, 98)
          << QColor(172, 153, 89)
          << QColor(145, 158, 93)
          << QColor(102, 139, 94)
          << QColor(97, 178, 144)
          << QColor(123, 186, 166)
          << QColor(41, 122, 126)
          << QColor(85, 120, 141)
          << QColor(112, 138, 178)
          << QColor(152, 140, 170)
          << QColor(115, 88, 119)
          << QColor(143, 102, 130)
          << QColor(186, 122, 142);
    d->chart = new HTm30BarChart(16);
    d->chart->axisX()->setTitleText("<p>Hue-Angle Bin (j)</p>");
    d->chart->axisY()->setTitleText("<p>Local Color Fidelity (R<span style='vertical-align:sub;'>f,hj</span>)</p>");
    d->chart->series()->setLabelsPrecision(2);
    d->chart->setBarColor(color);
    setChart(d->chart);
    HZoomChartView::init();
}

