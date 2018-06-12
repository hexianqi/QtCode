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
    void vernierChanged(QPointF pos);
    void vernierChanged();

public:
    virtual void setValidRegion(QRectF value) override;
    virtual void setVernierColor(QColor value);
    virtual void setVernier(int size);
    virtual void setVernier(int i, double percent);

public:
    QVector<QPointF> verniers();

public:
    virtual void paintEvent(QStylePainter *) override;
    virtual bool mousePressEvent(QMouseEvent *) override;
    virtual bool mouseMoveEvent(QMouseEvent *) override;
    virtual bool mouseReleaseEvent(QMouseEvent *) override;

protected:
    HVernierTracking(HVernierTrackingPrivate &p, QWidget *parent = nullptr);
};

#endif // HVERNIERTRACKING_H
