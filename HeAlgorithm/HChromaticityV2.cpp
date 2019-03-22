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

void HChromaticityV2::calcSpectrum(HSpecData *sp)
{
    Q_D(HChromaticityV2);
    if (sp->Energy.isEmpty())
        return;

    sp->CoordinateUv = d->cie1931->calcCoordinateUv(sp->Energy);
    d->cieUcs->calcColorTemperature(sp->CoordinateUv, sp->ColorTemperature, sp->Duv);
    sp->CoordinateXy = HSpecHelper::uv2xy(sp->CoordinateUv);
    sp->CoordinateUvp = HSpecHelper::uv2uvp(sp->CoordinateUv);
    d->cie1931->calcDominantWave(sp->CoordinateXy, sp->DominantWave, sp->ColorPurity);
    sp->RenderingIndex = calcColorRenderingIndex(sp->CoordinateUv, sp->Energy, sp->ColorTemperature);
    sp->RenderingIndexAvg = calcColorRenderingIndexAvg(sp->RenderingIndex);
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
