#include "HChromaticityV2.h"
#include "ISpectrumData.h"
#include "HCie.h"
#include "HSpectrum.h"

HE_ALGORITHM_BEGIN_NAMESPACE

HChromaticityV2::HChromaticityV2()
{
    _cieUcs = std::make_shared<HCieUcs>();
}

void HChromaticityV2::calcSpectrum(ISpectrumData *sp)
{
    if (sp->Energy.isEmpty())
        return;

    sp->CoordinateUv = _cie1931->calcCoordinateUv(sp->Energy);
    _cieUcs->calcColorTemperature(sp->CoordinateUv, sp->ColorTemperature, sp->Duv);
    sp->CoordinateXy = HSpectrum::uv2xy(sp->CoordinateUv);
    sp->CoordinateUvp = HSpectrum::uv2uvp(sp->CoordinateUv);
    _cie1931->calcDominantWave(sp->CoordinateXy, sp->DominantWave, sp->ColorPurity);
    sp->RenderingIndex = calcColorRenderingIndex(sp->CoordinateUv, sp->Energy, sp->ColorTemperature);
    sp->RenderingIndexAvg = calcColorRenderingIndexAvg(sp->RenderingIndex);
}

QVector<double> HChromaticityV2::calcColorRenderingIndex(QPointF uvk, QPolygonF spdk, double tc)
{
    auto ucs = _cieUcs->getCieUcs(tc);
    if (ucs.Tc < 2300)
        ucs = calcCieUcs(tc);
    return HChromaticity::calcColorRenderingIndex(uvk, spdk, ucs);
}

HE_ALGORITHM_END_NAMESPACE
