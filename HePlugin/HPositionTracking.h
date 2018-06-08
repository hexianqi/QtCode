#ifndef HPOSITIONTRACKING_H
#define HPOSITIONTRACKING_H

#include <QLabel>

class HPositionTrackingPrivate;

class HPositionTracking : public QLabel
{
    Q_OBJECT

public:
    explicit HPositionTracking(QWidget *parent = nullptr);
    ~HPositionTracking();

signals:
    void positionChanged(QPoint pos);

public:
    void setValidRegion(QRectF value);
    void setEnableTracking(bool b);

public:
    bool isEnableTracking();

public:
    virtual void mouseMoveEvent(QMouseEvent *) override;

protected:
    QScopedPointer<HPositionTrackingPrivate> d_ptr;
};

#endif // HPOSITIONTRACKING_H
