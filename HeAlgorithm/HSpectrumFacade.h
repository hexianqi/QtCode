#ifndef HSPECTRUMHELPER_H
#define HSPECTRUMHELPER_H

#include "IChromaticity.h"
#include <QScopedPointer>
#include <memory>

class HSpectrumFacadePrivate;

namespace He {
namespace Algorithm {
namespace Spectrum {

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
    std::shared_ptr<IChromaticity> getChromaticity();

private:
    QScopedPointer<HSpectrumFacadePrivate> d_ptr;
};

} // namespace Spectrum
} // namespace Algorithm
} // namespace He

#endif // HSPECTRUMHELPER_H
