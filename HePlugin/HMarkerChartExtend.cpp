#include "HMarkerChartExtend_p.h"
#include <QtCharts/QChart>
#include <QtCharts/QLegendMarker>

HMarkerChartExtend::HMarkerChartExtend(QObject *parent) :
    HAbstractChartExtend(*new HMarkerChartExtendPrivate, parent)
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

bool HMarkerChartExtend::connectExtend()
{
    if (!HAbstractChartExtend::connectExtend())
        return false;

    auto markers = chart()->legend()->markers();
    for (auto m : markers)
    {
        // Disconnect possible existing connection to avoid multiple connections
        disconnect(m, &QLegendMarker::clicked, this, &HMarkerChartExtend::handleMarkerClicked);
        connect(m, &QLegendMarker::clicked, this, &HMarkerChartExtend::handleMarkerClicked);
    }
    return true;
}

bool HMarkerChartExtend::disconnectExtend()
{
    if (!HAbstractChartExtend::disconnectExtend())
        return false;

    auto markers = chart()->legend()->markers();
    for (auto m : markers)
        disconnect(m, &QLegendMarker::clicked, this, &HMarkerChartExtend::handleMarkerClicked);
    return true;
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
