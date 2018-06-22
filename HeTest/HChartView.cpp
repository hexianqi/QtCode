#include "HChartView.h"
#include <QtCharts/QLegendMarker>
#include <QDebug>

HChartView::HChartView(QWidget *parent)
    : QChartView(parent)
{
    setRubberBand(QChartView::RectangleRubberBand);
}

HChartView::HChartView(QChart *chart, QWidget *parent)
    : QChartView(chart, parent)
{
    setRubberBand(QChartView::RectangleRubberBand);
}

void HChartView::connectMarkers()
{
    auto markers = chart()->legend()->markers();
    for (auto *marker : markers)
    {
        // Disconnect possible existing connection to avoid multiple connections
        disconnect(marker, &QLegendMarker::clicked, this, handleMarkerClicked);
        connect(marker, &QLegendMarker::clicked, this, handleMarkerClicked);
    }
}

void HChartView::disconnectMarkers()
{
    auto markers = chart()->legend()->markers();
    for (auto *marker : markers)
        disconnect(marker, &QLegendMarker::clicked, this, handleMarkerClicked);
}

void HChartView::handleMarkerClicked()
{
    auto marker = qobject_cast<QLegendMarker*> (sender());
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
    else
        qDebug() << "Unknown marker type";
}

void HChartView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Plus:
        chart()->zoomIn();
        break;
    case Qt::Key_Minus:
        chart()->zoomOut();
        break;
    case Qt::Key_Backspace:
        chart()->zoomReset();
        break;
    case Qt::Key_Left:
        chart()->scroll(-10, 0);
        break;
    case Qt::Key_Right:
        chart()->scroll(10, 0);
        break;
    case Qt::Key_Up:
        chart()->scroll(0, 10);
        break;
    case Qt::Key_Down:
        chart()->scroll(0, -10);
        break;
    default:
        QChartView::keyPressEvent(event);
        break;
    }
}


