#ifndef HCHROMATICITYV2_H
#define HCHROMATICITYV2_H

#include "HChromaticity.h"

namespace He {
namespace Algorithm {
namespace Spectrum {

class HChromaticityV2 : public HChromaticity
{
public:
    HChromaticityV2();

public:
    virtual void calcSpectrum(ISpectrumData *sp) override;

protected:
    virtual QVector<double> calcColorRenderingIndex(QPointF uvk, QPolygonF spdk, double tc) override;

protected:
    std::shared_ptr<HCieUcs> _cieUcs;
};

} // namespace Spectrum
} // namespace Algorithm
} // namespace He

#endif // HCHROMATICITYV2_H
