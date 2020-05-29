/***************************************************************************************************
**      2019-10-21  ITestElec 测试电数据接口。
***************************************************************************************************/

#ifndef ITESTELEC_H
#define ITESTELEC_H

#include "HDataType.h"
#include "HTestData.h"

HE_DATA_BEGIN_NAMESPACE

class IElecCalibrateCollection;

class ITestElec : public HTestData
{
public:
    using HTestData::HTestData;

public:
    // 设置校准数据
    virtual bool setCalibrate(IElecCalibrateCollection *) = 0;
};

HE_DATA_END_NAMESPACE

#endif // ITESTELEC_H
