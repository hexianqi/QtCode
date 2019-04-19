#include "HChromaticityV2_p.h"
#include "HSpecData.h"
#include "HSpecHelper.h"

HE_ALGORITHM_BEGIN_NAMESPACE

HChromaticityV2Private::HChromaticityV2Private()
{
    cieUcs = std::make_shared<HCieUcs>();
}

HChromaticityV2::HChromaticityV2()
    : HChromaticity(*new HChromaticityV2Private)
{
}

HChromaticityV2::HChromaticityV2(HChromaticityV2Private &p)
    : HChromaticity(p)
{
}

HChromaticityV2::~HChromaticityV2()
{
}

void HChromaticityV2::calcSpectrum(HSpecData *data)
{
    Q_D(HChromaticityV2);
    if (data->Energy.isEmpty())
        return;

    data->CoordinateUv = d->cie1931->calcCoordinateUv(data->Energy);
    data->CoordinateXy = HSpecHelper::uv2xy(data->CoordinateUv);
    data->CoordinateUvp = HSpecHelper::uv2uvp(data->CoordinateUv);
    d->cieUcs->calcColorTemperature(data->CoordinateUv, data->ColorTemperature, data->Duv);
    auto r = d_ptr->cie1931->calcDominantWavePurity(data->CoordinateXy);
    data->DominantWave = r.first();
    data->ColorPurity = r.last();
    data->RenderingIndex = calcColorRenderingIndex(data->CoordinateUv, data->Energy, data->ColorTemperature);
    data->RenderingIndexAvg = calcColorRenderingIndexAvg(data->RenderingIndex);
}

QVector<double> HChromaticityV2::calcColorRenderingIndex(QPointF uvk, QPolygonF spdk, double tc)
{
    Q_D(HChromaticityV2);
    auto ucs = d->cieUcs->getCieUcs(tc);
    if (ucs.Tc < 2300)
        ucs = calcCieUcs(tc);
    return HChromaticity::calcColorRenderingIndex(uvk, spdk, ucs);
}

HE_ALGORITHM_END_NAMESPACE
