#ifndef ICHROMATICITY_H
#define ICHROMATICITY_H

#include "HAlgorithmGlobal.h"

HE_ALGORITHM_BEGIN_NAMESPACE

class ISpectrumData;

// 色度参数计算接口
class HE_ALGORITHM_EXPORT IChromaticity
{
public:
    virtual void calcSpectrum(ISpectrumData *sp) = 0;
};

HE_ALGORITHM_END_NAMESPACE

#endif // ICHROMATICITY_H
