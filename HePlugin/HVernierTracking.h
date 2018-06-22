/***************************************************************************************************
**      2018-06-19  HVernierTracking 游标追踪策略。
***************************************************************************************************/

#ifndef HVERNIERTRACKING_H
#define HVERNIERTRACKING_H

#include "HAbstractMouseStrategy.h"
#include <QPointF>

class HVernierTrackingPrivate;

class HVernierTracking : public HAbstractMouseStrategy
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HVernierTracking)

public:
    explicit HVernierTracking(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~HVernierTracking();

signals:
    void orientationChanged(Qt::Orientation value);
    void vernierChanged(QPointF pos);
    void vernierSizeChanged(int size);

public:
    virtual void setOrientation(Qt::Orientation value);
    virtual void setValidRegion(QRectF value) override;
    virtual void setVernierColor(QColor value);
    virtual void setVernier(int i, double percent);
    virtual void resizeVernier(int size);


public:
    Qt::Orientation orientation();
    QVector<QPointF> verniers();

public:
    virtual void paintEvent(QPaintEvent *) override;
    virtual bool mousePressEvent(QMouseEvent *) override;
    virtual bool mouseMoveEvent(QMouseEvent *) override;
    virtual bool mouseReleaseEvent(QMouseEvent *) override;

protected:
    HVernierTracking(HVernierTrackingPrivate &p, QWidget *parent = nullptr);
};

#endif // HVERNIERTRACKING_H
