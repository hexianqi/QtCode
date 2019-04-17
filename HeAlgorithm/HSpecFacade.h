/***************************************************************************************************
**      2018-06-19  HSpectrumFacade 光谱计算外观类。
***************************************************************************************************/

#ifndef HSPECFACADE_H
#define HSPECFACADE_H

#include "HAlgorithmGlobal.h"
#include <QtCore/QScopedPointer>
#include <memory>

HE_ALGORITHM_BEGIN_NAMESPACE

class HSpecData;
class IChromaticity;
class HSpecFacadePrivate;

class HE_ALGORITHM_EXPORT HSpecFacade
{
public:
    HSpecFacade();
    ~HSpecFacade();

public:
    // 计算光谱参数
    void calcSpectrum(HSpecData *);
    // 设置色度参数计算方法
    void setChromaticity(int type);
    // 获取色度参数计算方法
    std::shared_ptr<IChromaticity> getChromaticity();

private:
    QScopedPointer<HSpecFacadePrivate> d_ptr;
};

HE_ALGORITHM_END_NAMESPACE

#endif // HSPECFACADE_H
