/***************************************************************************************************
**      2018-06-19  HVernierWidget 带游标图表窗口部件。
***************************************************************************************************/

#ifndef HVERNIERWIDGET_H
#define HVERNIERWIDGET_H

#include "HCartesianWidget.h"

class HVernierWidgetPrivate;
class HVernierTracking;
class QLabel;

class QDESIGNER_WIDGET_EXPORT HVernierWidget : public HCartesianWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HVernierWidget)
    Q_PROPERTY(int decimals READ decimals WRITE setDecimals)

public:
    explicit HVernierWidget(QWidget *parent = nullptr);
    ~HVernierWidget() override;

signals:
    void vernierValueChanged(QVector<double> value);
    void vernierTextChanged(QString value);

public:
    void setDecimals(int value);
    void updataVernier();

public:
    HVernierTracking *tracking();
    QLabel *labelLeft();
    QLabel *labelCenter();
    QLabel *labelRight();
    int decimals();

protected:
    HVernierWidget(HVernierWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    void setPlotArea(QRectF value) override;
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void handleCoordinateChanged(HCartesianCoordinate *) override;
    void handleOrientationChanged();
    void handleVernierPosChanged(QPointF pos);
    void handleVernierSizeChanged();

private:
    void init();
};

#endif // HVERNIERWIDGET_H
