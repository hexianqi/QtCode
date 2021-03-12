#include "HChromaticity2_p.h"
#include "HSpecData.h"
#include "HSpecHelper.h"
#include <QtCore/QDebug>

HE_ALGORITHM_BEGIN_NAMESPACE

HChromaticity2Private::HChromaticity2Private()
{
    cieUcs = std::make_shared<HCieUcs>();
}

HChromaticity2::HChromaticity2() :
    HChromaticity(*new HChromaticity2Private)
{
}

HChromaticity2::HChromaticity2(HChromaticity2Private &p) :
    HChromaticity(p)
{
}

HChromaticity2::~HChromaticity2()
{
    qDebug() << __func__;
}

void HChromaticity2::calcSpectrum(HSpecData *data)
{
    Q_D(HChromaticity2);
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

QVector<double> HChromaticity2::calcColorRenderingIndex(QPointF uvk, const QPolygonF &spdk, double tc)
{
    Q_D(HChromaticity2);
    auto ucs = d->cieUcs->findCieUcs(tc);
    if (ucs.Tc < 2300)
        ucs = calcCieUcs(tc);
    return HChromaticity::calcColorRenderingIndex(uvk, spdk, ucs);
}

HE_ALGORITHM_END_NAMESPACE
