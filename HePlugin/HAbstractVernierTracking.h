/***************************************************************************************************
**      2018-07-03  HAbstractVernierTracking 抽象游标追踪策略。
***************************************************************************************************/

#ifndef HABSTRACTVERNIERTRACKING_H
#define HABSTRACTVERNIERTRACKING_H

#include "HAbstractMouseStrategy.h"
#include <QPointF>

class HAbstractVernierTrackingPrivate;

class HAbstractVernierTracking : public HAbstractMouseStrategy
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAbstractVernierTracking)

public:
    explicit HAbstractVernierTracking(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~HAbstractVernierTracking() override;

signals:
    void orientationChanged(Qt::Orientation value);
    void vernierPosChanged(QPointF pos);
    void vernierSizeChanged(int size);

public:
    virtual bool setValidRegion(QRectF value) override;
    virtual void setOrientation(Qt::Orientation value);
    virtual void setVernierColor(QColor value);
    virtual void setVernier(int i, double percent);
    virtual void resizeVernier(int size);

public:
    Qt::Orientation orientation();
    QVector<QPointF> verniers();

public:
    bool mousePressEvent(QMouseEvent *) override;
    bool mouseReleaseEvent(QMouseEvent *) override;

protected:
    HAbstractVernierTracking(HAbstractVernierTrackingPrivate &p, QWidget *parent = nullptr);
};

#endif // HABSTRACTVERNIERTRACKING_H
