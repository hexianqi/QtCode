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
    ~HVernierWidget();

signals:
    void vernierValueChanged(QVector<double> value);
    void vernierTextChanged(QString value);

public:
    void setDecimals(int value);

public:
    HVernierTracking *tracking();
    QLabel *labelLeft();
    QLabel *labelCenter();
    QLabel *labelRight();
    int decimals();

protected:
    HVernierWidget(HVernierWidgetPrivate &p, QWidget *parent = nullptr);

protected:
    virtual void setPlotArea(QRectF value) override;
    virtual void paintEvent(QPaintEvent *) override;
    virtual void mousePressEvent(QMouseEvent *) override;
    virtual void mouseMoveEvent(QMouseEvent *) override;
    virtual void mouseReleaseEvent(QMouseEvent *) override;
    virtual void handleCoordinateChanged(HCartesianCoordinate *) override;
    virtual void handleOrientationChanged();
    virtual void handleVernierChanged(QPointF pos);
    virtual void handleVernierSizeChanged();
    void updateVernierValue();
    QString toString(QVector<double> value);

private:
    void init();
};

#endif // HVERNIERWIDGET_H
