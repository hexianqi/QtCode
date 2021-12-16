/***************************************************************************************************
**      2018-06-19  IProtocol 协议接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"
#include "HeCore/HActionType.h"

HE_BEGIN_NAMESPACE

class IDevice;

class IProtocol : public IInitializeable
{
public:
    // 端口类型
    virtual QString portType() = 0;
    // 设置设备
    virtual void setDevice(IDevice *) = 0;
    // 打开
    virtual bool open() = 0;
    // 关闭
    virtual bool close() = 0;

public:
    // 设置数据
    virtual bool setData(HActionType action, int value, int delay = 0) = 0;
    virtual bool setData(HActionType action, uchar value, int delay = 0) = 0;
    virtual bool setData(HActionType action, uint value, int delay = 0) = 0;
    virtual bool setData(HActionType action, double value, int delay = 0) = 0;
    virtual bool setData(HActionType action, QVector<int> value, int delay = 0) = 0;
    virtual bool setData(HActionType action, QVector<uchar> value, int delay = 0) = 0;
    virtual bool setData(HActionType action, QVector<uint> value, int delay = 0) = 0;
    virtual bool setData(HActionType action, QVector<double> value, int delay = 0) = 0;
    // 读取数据
    virtual bool getData(HActionType action, int &value, int delay = 0) = 0;
    virtual bool getData(HActionType action, uchar &value, int delay = 0) = 0;
    virtual bool getData(HActionType action, uint &value, int delay = 0) = 0;
    virtual bool getData(HActionType action, QVector<int> &value, int delay = 0) = 0;
    virtual bool getData(HActionType action, QVector<uchar> &value, int delay = 0) = 0;
    virtual bool getData(HActionType action, QVector<uint> &value, int delay = 0) = 0;
    virtual bool getData(HActionType action, QVector<double> &value, int delay = 0) = 0;
};

HE_END_NAMESPACE
