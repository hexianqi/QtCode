#include "HTm30RhshjChartView_p.h"
#include "HTm30BarChart.h"
#include <QtCharts/QBarSeries>
#include <QtCharts/QValueAxis>

HTm30RhshjChartView::HTm30RhshjChartView(QWidget *parent) :
    HZoomChartView(*new HTm30RhshjChartViewPrivate, nullptr, parent)
{
    init();
}

HTm30RhshjChartView::~HTm30RhshjChartView()
{
}

HTm30BarChart *HTm30RhshjChartView::chart()
{
    Q_D(HTm30RhshjChartView);
    return d->chart;
}

void HTm30RhshjChartView::init()
{
    Q_D(HTm30RhshjChartView);

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
    d->chart->axisY()->setTitleText("<p>Local Hue Shift (R<span style='vertical-align:sub;'>hs,hj</span>)</p>");
    d->chart->axisY()->setRange(-0.6, 0.6);
    d->chart->series()->setLabelsPrecision(2);
    d->chart->series()->setLabelsAngle(90);
    d->chart->setBarColor(color);
    setChart(d->chart);
    HZoomChartView::init();
}

