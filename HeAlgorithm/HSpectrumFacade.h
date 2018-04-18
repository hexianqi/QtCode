#ifndef HSPECTRUMHELPER_H
#define HSPECTRUMHELPER_H

#include "IChromaticity.h"
#include <memory>

namespace He {
namespace Algorithm {
namespace Spectrum {

class HPhotopicVision;

// 光谱计算外观类
class HEALGORITHM_EXPORT HSpectrumFacade
{
public:
    HSpectrumFacade();

public:
    // 计算光谱参数
    void calcSpectrum(ISpectrumData *sp);
    // 设置色度参数计算方法
    void setChromaticity(int type);
    // 获取色度参数计算方法
    std::shared_ptr<IChromaticity> getChromaticity() { return _chromaticity; }

protected:
    int _chromaticityType;
    std::shared_ptr<IChromaticity> _chromaticity;
    std::shared_ptr<HPhotopicVision> _photopicVision;
};

} // namespace Spectrum
} // namespace Algorithm
} // namespace He

#endif // HSPECTRUMHELPER_H
