#ifndef HABSTRACTDOMAIN_H
#define HABSTRACTDOMAIN_H

#include <QObject>

class HAbstractDomainPrivate;

class HAbstractDomain : public QObject
{
    Q_OBJECT

public:
    explicit HAbstractDomain(QObject *parent = nullptr);
    ~HAbstractDomain();

signals:
    void updated();
    void rangeHorizontalChanged(double min, double max);
    void rangeVerticalChanged(double min, double max);

public:
    void setRangeX(double min, double max);
    void setRangeY(double min, double max);
    void setMinX(double min);
    void setMaxX(double max);
    void setMinY(double min);
    void setMaxY(double max);
    void setBlockRangeSignals(bool b);
    void zoomReset();
    void storeZoomReset();

public:
    double minX() const;
    double maxX() const;
    double minY() const;
    double maxY() const;
    double spanX() const;
    double spanY() const;
    bool isEmpty() const;
    bool isRangeSignalsBlocked() const;
    bool isZoomed();

public:
    virtual void setRange(double minX, double maxX, double minY, double maxY) = 0;
    virtual bool zoomIn(QRectF &rect) = 0;
    virtual bool zoomOut(QRectF &rect) = 0;
    virtual QPointF calcDomainPoint(QPointF &point) const = 0;
    virtual QPointF calcGeometryPoint(QPointF &point, bool &ok) const = 0;
    virtual QVector<QPointF> calcGeometryPoints(QVector<QPointF> &vector) const = 0;

protected:
    HAbstractDomain(HAbstractDomainPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HAbstractDomainPrivate> d_ptr;
};

#endif // HABSTRACTDOMAIN_H
