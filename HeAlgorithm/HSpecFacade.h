/***************************************************************************************************
**      2018-06-19  HSpectrumFacade 光谱计算外观类。
***************************************************************************************************/

#pragma once

#include "HNamespace.h"
#include <QtCore/QScopedPointer>

HE_BEGIN_NAMESPACE

class IChromaticity;
class HSpecData;
class HSpecFacadePrivate;

class HSpecFacade
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
    IChromaticity *chromaticity();

private:
    QScopedPointer<HSpecFacadePrivate> d_ptr;
};

HE_END_NAMESPACE
