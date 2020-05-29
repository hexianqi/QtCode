/***************************************************************************************************
**      2020-05-25  ITestLuminous 测试光数据接口。
***************************************************************************************************/

#pragma once

#include "HDataType.h"
#include "HTestData.h"

HE_DATA_BEGIN_NAMESPACE

class ILuminousCalibrateCollection;

class ITestLuminous : public HTestData
{
public:
    using HTestData::HTestData;

public:
    // 设置校准数据
    virtual bool setCalibrate(ILuminousCalibrateCollection *) = 0;
};

HE_DATA_END_NAMESPACE
