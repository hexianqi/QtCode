#include "HTm30RcshjChartView_p.h"
#include "HTm30BarChart.h"
#include <QtCharts/QBarSeries>
#include <QtCharts/QValueAxis>

HTm30RcshjChartView::HTm30RcshjChartView(QWidget *parent) :
    HZoomChartView(*new HTm30RcshjChartViewPrivate, nullptr, parent)
{
    init();
}

HTm30RcshjChartView::~HTm30RcshjChartView()
{
}

HTm30BarChart *HTm30RcshjChartView::chart()
{
    Q_D(HTm30RcshjChartView);
    return d->chart;
}

void HTm30RcshjChartView::init()
{
    Q_D(HTm30RcshjChartView);

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
    auto axisY = qobject_cast<QValueAxis *>(d->chart->axisY());
    axisY->setTitleText("<p>Local Chroma Shift (R<span style='vertical-align:sub;'>cs,hj</span>)</p>");
    axisY->setRange(-50, 50);
    axisY->setLabelFormat("%d%");
    d->chart->axisX()->setTitleText("<p>Hue-Angle Bin (j)</p>");
    d->chart->series()->setLabelsFormat("@value%");
    d->chart->series()->setLabelsPrecision(2);
    d->chart->series()->setLabelsAngle(90);
    d->chart->setBarColor(color);
    setChart(d->chart);
    setWindowTitle(tr("色度变化"));
    HZoomChartView::init();
}

