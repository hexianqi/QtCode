#ifndef HCHARTVIEW_H
#define HCHARTVIEW_H

#include <QtCharts/QChartView>

QT_CHARTS_USE_NAMESPACE

class HChartView : public QChartView
{
    Q_OBJECT

public:
    explicit HChartView(QWidget *parent = nullptr);
    explicit HChartView(QChart *chart, QWidget *parent = nullptr);

public slots:
    void connectMarkers();
    void disconnectMarkers();
    void handleMarkerClicked();

protected:
    virtual void keyPressEvent(QKeyEvent *) override;
};

#endif // HCHARTVIEW_H
