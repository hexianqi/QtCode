/***************************************************************************************************
**      2018-06-19  IProtocol 协议接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"
#include "HeCore/HActionType.h"

HE_BEGIN_NAMESPACE

class IDevice;
class IPort;
class IUCharConvert;

class IProtocol : public IInitializeable
{
public:
    // 端口类型
    virtual QString portType() = 0;
    // 设置设备
    virtual void setDevice(IDevice *) = 0;
    // 设置转换器
    virtual void setConvert(IUCharConvert *) = 0;
    // 设置端口
    virtual void setPort(IPort *, int num = 0, bool autoScan = true) = 0;
    // 打开
    virtual bool open() = 0;
    // 关闭
    virtual bool close() = 0;

public:
    // 设置数据
    virtual bool setData(HActionType action) = 0;
    virtual bool setData(HActionType action, QVariant value, int delay = 0) = 0;
    virtual bool setData(HActionType action, QVariantList value, int delay = 0) = 0;
    virtual bool setData(HActionType action, QVector<uchar> value, int delay = 0) = 0;

public:
    // 读取数据
    virtual bool getData(HActionType action) = 0;
    virtual bool getData(HActionType action, QVariant &value, QVariant::Type type = QVariant::Int, int delay = 0) = 0;
    virtual bool getData(HActionType action, QVariantList &value, QVariant::Type type = QVariant::Int, int delay = 0) = 0;
    virtual bool getData(HActionType action, QVector<uchar> &value, int delay = 0) = 0;
};

HE_END_NAMESPACE
