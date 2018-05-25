#ifndef HLIGHTSOURCE_H
#define HLIGHTSOURCE_H

#include "IChromaticity.h"
#include "HCie.h"
#include <QScopedPointer>

HE_ALGORITHM_BEGIN_NAMESPACE

class HChromaticityPrivate;

// 色度参数计算类
class HChromaticity : public IChromaticity
{
public:
    explicit HChromaticity();
    virtual ~HChromaticity();

public:
    virtual void calcSpectrum(ISpectrumData *) override;
    virtual QLineF calcIsothermUv(double tc, double duv) override;
    virtual QLineF calcIsothermXy(double tc, double duv) override;
    virtual QLineF calcIsothermUv(double tc, double duvB, double duvE) override;
    virtual QLineF calcIsothermXy(double tc, double duvB, double duvE) override;

public:
    virtual bool exportIsotherm(QString fileName, QPointF tc, double interval = 1.0) override;
    virtual bool exportIsotherm(QString fileName) override;
    virtual bool exportCieUcs(QString fileName, QPointF tc = QPointF(1400, 25000), double interval = 1.0) override;

protected:
    HChromaticity(HChromaticityPrivate &p);

protected:
    virtual QVector<double> calcColorRenderingIndex(QPointF uvk, QPolygonF spdk, double tc);
    virtual QVector<double> calcColorRenderingIndex(QPointF uvk, QPolygonF spdk, CIE_UCS refer);
    virtual double calcColorRenderingIndexAvg(QVector<double> index);

protected:
    CIE_UCS calcCieUcs(double tc);
    bool exportIsotherm(QString fileName, QVector<ISOTHERM> data);

protected:
    QScopedPointer<HChromaticityPrivate> d_ptr;
};

HE_ALGORITHM_END_NAMESPACE

#endif // HLIGHTSOURCE_H
