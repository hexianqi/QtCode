#ifndef ICHROMATICITY_H
#define ICHROMATICITY_H

#include "HeAlgorithm_global.h"

namespace He {
namespace Algorithm {
namespace Spectrum {

class ISpectrumData;

// 色度参数计算接口
class HEALGORITHM_EXPORT IChromaticity
{
public:
    virtual void calcSpectrum(ISpectrumData *sp) = 0;
};

} // namespace Spectrum
} // namespace Algorithm
} // namespace He

#endif // ICHROMATICITY_H
