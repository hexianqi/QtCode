/***************************************************************************************************
**      2018-06-19  HPositionTracking 鼠标追踪策略。
***************************************************************************************************/

#ifndef HPOSITIONTRACKING_H
#define HPOSITIONTRACKING_H

#include "HAbstractMouseStrategy.h"
#include <QPointF>

class QLabel;
class HPositionTrackingPrivate;

class HPositionTracking : public HAbstractMouseStrategy
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HPositionTracking)

public:
    explicit HPositionTracking(QWidget *parent = nullptr);
    ~HPositionTracking();

signals:
    void positionChanged(QPointF pos);

public:
    virtual void setValidRegion(QRectF value) override;
    virtual void setEnable(bool b) override;
    virtual void setText(QString text);

public:
    QLabel *label();

public:
    virtual void paintEvent(QPaintEvent *) override;
    virtual bool mousePressEvent(QMouseEvent *) override;
    virtual bool mouseMoveEvent(QMouseEvent *) override;
    virtual bool mouseReleaseEvent(QMouseEvent *) override;

protected:
    HPositionTracking(HPositionTrackingPrivate &p, QWidget *parent = nullptr);
};

#endif // HPOSITIONTRACKING_H
