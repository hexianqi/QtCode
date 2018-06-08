#ifndef HVERNIERTRACKING_H
#define HVERNIERTRACKING_H

#include <QWidget>

class HVernierTrackingPrivate;

class HVernierTracking : public QWidget
{
    Q_OBJECT

public:
    explicit HVernierTracking(Qt::Orientation orientation, QWidget *parent = nullptr);
    ~HVernierTracking();

signals:
    void vernierChanged(QPointF pos);
    void vernierChanged();

public:
    void setValidRegion(QRectF value);
    void setEnableTracking(bool b);
    void setVernierColor(QColor value);
    void setVernier(int size);
    void setVernier(int i, double percent);

public:
    bool isEnableTracking();

public:
    virtual void paintEvent(QPaintEvent *) override;
    virtual void mousePressEvent(QMouseEvent *) override;
    virtual void mouseMoveEvent(QMouseEvent *) override;
    virtual void mouseReleaseEvent(QMouseEvent *) override;


protected:
    QScopedPointer<HVernierTrackingPrivate> d_ptr;
};

#endif // HVERNIERTRACKING_H
