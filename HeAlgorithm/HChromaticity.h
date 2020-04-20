/***************************************************************************************************
**      2018-06-19  HChromaticity 色度参数计算类。
***************************************************************************************************/

#ifndef HLIGHTSOURCE_H
#define HLIGHTSOURCE_H

#include "IChromaticity.h"
#include "HCie.h"
#include <QtCore/QScopedPointer>

HE_ALGORITHM_BEGIN_NAMESPACE

class HChromaticityPrivate;

class HE_ALGORITHM_EXPORT HChromaticity : public IChromaticity
{
public:
    explicit HChromaticity();
    virtual ~HChromaticity();

public:
    void calcSpectrum(HSpecData *) override;
    QLineF calcIsothermUv(double tc, double duv) override;
    QLineF calcIsothermUv(double tc, double duvB, double duvE) override;
    QLineF calcIsothermXy(double tc, double duv) override;
    QLineF calcIsothermXy(double tc, double duvB, double duvE) override;

public:
    bool exportIsotherm(const QString &fileName, QPointF tc, double interval = 1.0) override;
    bool exportIsotherm(const QString &fileName) override;
    bool exportCieUcs(const QString &fileName, QPointF tc = QPointF(1400, 25000), double interval = 1.0) override;

protected:
    HChromaticity(HChromaticityPrivate &);

protected:
    virtual QVector<double> calcColorRenderingIndex(QPointF uvk, const QPolygonF &spdk, double tc);
    virtual QVector<double> calcColorRenderingIndex(QPointF uvk, const QPolygonF &spdk, CIE_UCS refer);
    virtual double calcColorRenderingIndexAvg(QVector<double> index);

protected:
    CIE_UCS calcCieUcs(double tc);
    bool exportIsotherm(const QString &fileName, QList<ISOTHERM> data);

protected:
    QScopedPointer<HChromaticityPrivate> d_ptr;
};

HE_ALGORITHM_END_NAMESPACE

#endif // HLIGHTSOURCE_H
