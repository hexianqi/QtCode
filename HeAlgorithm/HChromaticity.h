/***************************************************************************************************
**      2018-06-19  HChromaticity 色度参数计算类。
***************************************************************************************************/

#pragma once

#include "IChromaticity.h"
#include "HCie.h"
#include <QtCore/QScopedPointer>

HE_BEGIN_NAMESPACE

class HChromaticityPrivate;

class HChromaticity : public IChromaticity
{
public:
    explicit HChromaticity();
    virtual ~HChromaticity();

public:
    void calcSpectrum(HSpecData *) override;
    QLineF calcIsothermUV(double tc, double duv) override;
    QLineF calcIsothermUV(double tc, double duvB, double duvE) override;
    QLineF calcIsothermXY(double tc, double duv) override;
    QLineF calcIsothermXY(double tc, double duvB, double duvE) override;

public:
    bool exportIsotherm(const QString &fileName, QPointF tc, double interval = 1.0) override;
    bool exportIsotherm(const QString &fileName) override;
    bool exportCieUcs(const QString &fileName, QPointF tc = QPointF(1400, 25000), double interval = 1.0) override;

protected:
    HChromaticity(HChromaticityPrivate &);

protected:
    virtual QList<double> calcColorTemperatureDuv(QPointF uv);
    virtual QVector<double> calcColorRenderingIndex(QPointF uvk, const QPolygonF &spdk, double tc);
    virtual QVector<double> calcColorRenderingIndex(QPointF uvk, const QPolygonF &spdk, CIE_UCS refer);
    virtual double calcColorRenderingIndexAvg(QVector<double> index);

protected:
    CIE_UCS calcCieUcs(double tc);

protected:
    bool exportIsotherm(const QString &fileName, QList<ISOTHERM> data);
    bool exportCieUcs(const QString &fileName, QList<CIE_UCS> data);

protected:
    QScopedPointer<HChromaticityPrivate> d_ptr;
};

HE_END_NAMESPACE
