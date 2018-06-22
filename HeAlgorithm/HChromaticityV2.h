/***************************************************************************************************
**      2018-06-19  HChromaticityV2 第2版色度参数计算类。
**                  与第一版区别在于显色指数计算方式。
***************************************************************************************************/

#ifndef HCHROMATICITYV2_H
#define HCHROMATICITYV2_H

#include "HChromaticity.h"

HE_ALGORITHM_BEGIN_NAMESPACE

class HChromaticityV2Private;

class HChromaticityV2 : public HChromaticity
{
    Q_DECLARE_PRIVATE(HChromaticityV2)

public:
    explicit HChromaticityV2();
    ~HChromaticityV2();

public:
    virtual void calcSpectrum(ISpectrumData *) override;

protected:
    virtual QVector<double> calcColorRenderingIndex(QPointF uvk, QPolygonF spdk, double tc) override;

protected:
    HChromaticityV2(HChromaticityV2Private &p);
};

HE_ALGORITHM_END_NAMESPACE

#endif // HCHROMATICITYV2_H
