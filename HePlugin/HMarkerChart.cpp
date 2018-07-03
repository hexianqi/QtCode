#include "HMarkerChart_p.h"
#include <QtCharts/QLegendMarker>

HMarkerChartPrivate::HMarkerChartPrivate(HMarkerChart *q)
    : q_ptr(q)
{
}

HMarkerChart::HMarkerChart(QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(parent, wFlags), d_ptr(new HMarkerChartPrivate(this))
{
}

HMarkerChart::HMarkerChart(HMarkerChartPrivate &p, QGraphicsItem *parent, Qt::WindowFlags wFlags)
    : QChart(parent, wFlags), d_ptr(&p)
{
}

HMarkerChart::~HMarkerChart()
{
}

void HMarkerChart::connectMarkers()
{
    auto markers = legend()->markers();
    for (auto *marker : markers)
    {
        // Disconnect possible existing connection to avoid multiple connections
        disconnect(marker, &QLegendMarker::clicked, this, handleMarkerClicked);
        connect(marker, &QLegendMarker::clicked, this, handleMarkerClicked);
    }
}

void HMarkerChart::disconnectMarkers()
{
    auto markers = legend()->markers();
    for (auto *marker : markers)
        disconnect(marker, &QLegendMarker::clicked, this, handleMarkerClicked);
}

void HMarkerChart::handleMarkerClicked()
{
    auto marker = qobject_cast<QLegendMarker*>(sender());
    if (marker->type() == QLegendMarker::LegendMarkerTypeXY)
    {
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
}
