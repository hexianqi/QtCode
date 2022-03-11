#include "HChartHelper.h"
#include <QtCharts/QPolarChart>
#include <QtCharts/QValueAxis>

QChart *HChartHelper::switchChartType(QChart *oldChart)
{
    auto newChart = oldChart->chartType() == QChart::ChartTypeCartesian ? new QPolarChart() : new QChart();
    // Move series and axes from old chart to new one
    auto seriesList = oldChart->series();
    auto axisList = oldChart->axes();
    QList<QPair<qreal, qreal>> axisRanges;

    for (auto axis : axisList)
    {
        auto valueAxis = qobject_cast<QValueAxis *>(axis);
        axisRanges.append(qMakePair(valueAxis->min(), valueAxis->max()));
    }

    for (auto series : seriesList)
        oldChart->removeSeries(series);

    for (auto axis : axisList)
    {
        oldChart->removeAxis(axis);
        newChart->addAxis(axis, axis->alignment());
    }

    for (auto series : seriesList)
    {
        newChart->addSeries(series);
        for (auto axis : axisList)
            series->attachAxis(axis);
    }

    int count = 0;
    for (auto axis : axisList)
    {
        axis->setRange(axisRanges[count].first, axisRanges[count].second);
        count++;
    }

    newChart->setTitle(oldChart->title());
    delete oldChart;
    return newChart;
}
