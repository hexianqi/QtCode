#ifndef HXYDOMAIN_H
#define HXYDOMAIN_H

#include "HAbstractDomain.h"

class HXYDomainPrivate;

class HXYDomain : public HAbstractDomain
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HXYDomain)

public:
    explicit HXYDomain(QObject *parent = nullptr);
    ~HXYDomain();

//public:
//    virtual void setRange(double minX, double maxX, double minY, double maxY) override;
//    virtual bool zoomIn(QRectF &rect) override;
//    virtual bool zoomOut(QRectF &rect) override;
//    virtual QPointF calcDomainPoint(QPointF &point) const override;
//    virtual QPointF calcGeometryPoint(QPointF &point, bool &ok) const override;
//    virtual QVector<QPointF> calcGeometryPoints(QVector<QPointF> &vector) const override;


protected:
    HXYDomain(HXYDomainPrivate &p, QObject *parent = nullptr);
};

#endif // HXYDOMAIN_H
