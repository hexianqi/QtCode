/***************************************************************************************************
**      2018-06-19  IDevice 设备接口。
***************************************************************************************************/

#pragma once

#include "HCommunicateGlobal.h"
#include "HeCore/IInitializeable.h"
#include "HeCore/HActionType.h"

HE_CORE_USE_NAMESPACE

HE_COMMUNICATE_BEGIN_NAMESPACE

class IPort;

class IDevice : public IInitializeable
{
public:
    // 端口类型
    virtual QString portType() = 0;
    // 是否支持命令
    virtual bool isSupport(HActionType action) = 0;
    // 设置通讯口
    virtual void setPort(IPort *port, int num = 0, bool scan = true) = 0;
    // 设置设备ID
    virtual void setDeviceID(int value) = 0;
    // 添加命令参数
    virtual void addActionParam(HActionType key, QList<uchar> value) = 0;

public:
    // 打开
    virtual bool open() = 0;
    // 关闭
    virtual bool close() = 0;
    // 设置数据
    virtual bool setData(HActionType action, QVector<uchar> value, int delay = 0) = 0;
    // 获取数据
    virtual bool getData(HActionType action, QVector<uchar> &value, int delay = 0) = 0;
};

HE_COMMUNICATE_END_NAMESPACE
