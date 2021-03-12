/***************************************************************************************************
**      2018-06-19  IDeviceCollection 设备集合接口。
***************************************************************************************************/

#pragma once

#include "HCommunicateGlobal.h"
#include "HeCore/HCollection.h"
#include "HeCore/HActionType.h"

HE_CORE_USE_NAMESPACE

HE_COMMUNICATE_BEGIN_NAMESPACE

class IDevice;

class IDeviceCollection : public HCollection<IDevice>
{
public:
    using HCollection::HCollection;

public:
    // 添加支持动作
    virtual void addSupport(HActionType action) = 0;
    // 是否支持
    virtual bool isSupport(HActionType action) = 0;
};

HE_COMMUNICATE_END_NAMESPACE
