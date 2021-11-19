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

QList<double> HChromaticity2::calcColorTemperatureDuv(QPointF uv)
{
    Q_D(HChromaticity2);
    return d->cieUcs->calcColorTemperatureDuv(uv);
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
