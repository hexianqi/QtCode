#ifndef HLIGHTSOURCE_H
#define HLIGHTSOURCE_H

#include "IChromaticity.h"
#include "HCie.h"
#include <QLineF>

HE_ALGORITHM_BEGIN_NAMESPACE

// 色度参数计算类
class HChromaticity : public IChromaticity
{
public:
    HChromaticity();
    virtual ~HChromaticity() = default;

public:
    // 计算光谱参数
    virtual void calcSpectrum(ISpectrumData *sp) override;
    // 计算等温线段
    QLineF calcIsothermUv(double tc, double duv);
    QLineF calcIsothermXy(double tc, double duv);
    QLineF calcIsothermUv(double tc, double duvB, double duvE);
    QLineF calcIsothermXy(double tc, double duvB, double duvE);

public:
    //导出等温线数据
    bool exportIsotherm(QString fileName, QPointF tc, double interval = 1.0);
    bool exportIsotherm(QString fileName);
    //导出UCS数据
    bool exportCieUcs(QString fileName, QPointF tc = QPointF(1400, 25000), double interval = 1.0);

protected:
    virtual QVector<double> calcColorRenderingIndex(QPointF uvk, QPolygonF spdk, double tc);
    virtual QVector<double> calcColorRenderingIndex(QPointF uvk, QPolygonF spdk, CIE_UCS refer);
    virtual double calcColorRenderingIndexAvg(QVector<double> index);

protected:
    CIE_UCS calcCieUcs(double tc);
    bool exportIsotherm(QString fileName, QVector<ISOTHERM> data);

protected:
    std::shared_ptr<HCie1931> _cie1931;
    std::shared_ptr<HCieDay> _cieDay;
    std::shared_ptr<HIsotherm> _isotherm;
};

HE_ALGORITHM_END_NAMESPACE

#endif // HLIGHTSOURCE_H
