#include "HMarkerChartExtend_p.h"
#include <QtCharts/QChart>
#include <QtCharts/QLegendMarker>

HMarkerChartExtendPrivate::HMarkerChartExtendPrivate(QChart *c) :
    HAbstractChartExtendPrivate(c)
{
}

HMarkerChartExtend::HMarkerChartExtend(QChart *chart, QObject *parent) :
    HAbstractChartExtend(*new HMarkerChartExtendPrivate(chart), parent)
{
}

HMarkerChartExtend::HMarkerChartExtend(HMarkerChartExtendPrivate &p, QObject *parent) :
    HAbstractChartExtend(p, parent)
{
}

HMarkerChartExtend::~HMarkerChartExtend()
{
}

void HMarkerChartExtend::connectMarkers()
{
    Q_D(HMarkerChartExtend);
    auto markers = d->chart->legend()->markers();
    for (auto marker : markers)
    {
        // Disconnect possible existing connection to avoid multiple connections
        disconnect(marker, &QLegendMarker::clicked, this, &HMarkerChartExtend::handleMarkerClicked);
        connect(marker, &QLegendMarker::clicked, this, &HMarkerChartExtend::handleMarkerClicked);
    }
}

void HMarkerChartExtend::disconnectMarkers()
{
    Q_D(HMarkerChartExtend);
    auto markers = d->chart->legend()->markers();
    for (auto marker : markers)
        disconnect(marker, &QLegendMarker::clicked, this, &HMarkerChartExtend::handleMarkerClicked);
}

void HMarkerChartExtend::handleMarkerClicked()
{
    auto marker = qobject_cast<QLegendMarker*>(sender());
    if (marker->type() != QLegendMarker::LegendMarkerTypeXY)
        return;

    marker->series()->setVisible(!marker->series()->isVisible());
    marker->setVisible(true);
    auto alpha = marker->series()->isVisible() ? 1.0 : 0.5;

    auto brush = marker->labelBrush();
    auto color = brush.color();
    color.setAlphaF(alpha);
    brush.setColor(color);
    marker->setLabelBrush(brush);

    brush = marker->brush();
    color = brush.color();
    color.setAlphaF(alpha);
    brush.setColor(color);
    marker->setBrush(brush);

    auto pen = marker->pen();
    color = pen.color();
    color.setAlphaF(alpha);
    pen.setColor(color);
    marker->setPen(pen);
}
