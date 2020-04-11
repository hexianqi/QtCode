/***************************************************************************************************
**      2018-07-03  HAbstractVernierTracking 抽象游标追踪策略。
***************************************************************************************************/

#ifndef HABSTRACTVERNIERTRACKING_H
#define HABSTRACTVERNIERTRACKING_H

#include "HAbstractMouseStrategy.h"
#include <QtCore/QPointF>

class HAbstractVernierTrackingPrivate;

class QDESIGNER_WIDGET_EXPORT HAbstractVernierTracking : public HAbstractMouseStrategy
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HAbstractVernierTracking)

public:
    explicit HAbstractVernierTracking(Qt::Orientation orientation, QWidget *parent = nullptr);

signals:
    void orientationChanged(Qt::Orientation value);
    void vernierPosChanged(QPointF pos);
    void vernierSizeChanged(int size);

public:
    virtual bool setValidRegion(QRectF value) override;
    virtual bool setOrientation(Qt::Orientation value);
    virtual bool setVernierColor(const QColor &value);
    virtual bool setVernier(int i, double percent);
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
