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

public:
    static void looseNiceNumbers(double &min, double &max, int &ticksCount);
    static qreal niceNumber(double x, bool ceiling);

public:
//    void zoomReset();
//    void storeZoomReset();

public:
    virtual bool zoomIn(const QRectF &rect) = 0;
    virtual bool zoomOut(const QRectF &rect) = 0;
    virtual QPointF calcDomainPoint(const QPointF &point) const = 0;
    virtual QPointF calcGeometryPoint(const QPointF &point, bool &ok) const = 0;
    virtual QVector<QPointF> calcGeometryPoints(const QVector<QPointF> &vector) const = 0;

protected:
    HAbstractDomain(HAbstractDomainPrivate &p, QObject *parent = nullptr);

protected:
    QScopedPointer<HAbstractDomainPrivate> d_ptr;
};

#endif // HABSTRACTDOMAIN_H
