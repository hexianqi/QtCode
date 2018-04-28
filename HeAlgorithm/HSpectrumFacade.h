#ifndef HSPECTRUMHELPER_H
#define HSPECTRUMHELPER_H

#include "HAlgorithmGlobal.h"
#include <QScopedPointer>
#include <memory>

HE_ALGORITHM_BEGIN_NAMESPACE

class ISpectrumData;
class IChromaticity;
class HSpectrumFacadePrivate;

// 光谱计算外观类
class HE_ALGORITHM_EXPORT HSpectrumFacade
{
public:
    HSpectrumFacade();
    ~HSpectrumFacade();

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

HE_ALGORITHM_END_NAMESPACE

#endif // HSPECTRUMHELPER_H
