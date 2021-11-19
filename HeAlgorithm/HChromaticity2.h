/***************************************************************************************************
**      2018-06-19  HChromaticityV2 第2版色度参数计算类。
**                  与第一版区别在于显色指数计算方式。
***************************************************************************************************/

#pragma once

#include "HChromaticity.h"

HE_ALGORITHM_BEGIN_NAMESPACE

class HChromaticity2Private;

class HChromaticity2 : public HChromaticity
{
    Q_DECLARE_PRIVATE(HChromaticity2)

public:
    explicit HChromaticity2();
    ~HChromaticity2() override;

protected:
    QList<double> calcColorTemperatureDuv(QPointF uv) override;
    QVector<double> calcColorRenderingIndex(QPointF uvk, const QPolygonF &spdk, double tc) override;

protected:
    HChromaticity2(HChromaticity2Private &);
};

HE_ALGORITHM_END_NAMESPACE
