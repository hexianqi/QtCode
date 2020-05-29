/***************************************************************************************************
**      2018-06-19  IProtocol 协议接口。
***************************************************************************************************/

#ifndef IPROTOCOL_H
#define IPROTOCOL_H

#include "HCommunicateGlobal.h"
#include "HeCore/IInitializeable.h"
#include "HeCore/HActionType.h"
#include "HeCore/HErrorType.h"

HE_CORE_USE_NAMESPACE

HE_COMMUNICATE_BEGIN_NAMESPACE

class IDevice;

class IProtocol : public IInitializeable
{
public:
    // 端口类型
    virtual QString portType() = 0;
    // 设置设备
    virtual void setDevice(IDevice *) = 0;
    // 打开
    virtual HErrorType open() = 0;
    // 关闭
    virtual HErrorType close() = 0;

public:
    // 设置数据
    virtual HErrorType setData(HActionType action, int value, int delay = 0) = 0;
    virtual HErrorType setData(HActionType action, uchar value, int delay = 0) = 0;
    virtual HErrorType setData(HActionType action, uint value, int delay = 0) = 0;
    virtual HErrorType setData(HActionType action, QVector<int> value, int delay = 0) = 0;
    virtual HErrorType setData(HActionType action, QVector<uchar> value, int delay = 0) = 0;
    virtual HErrorType setData(HActionType action, QVector<uint> value, int delay = 0) = 0;
    // 读取数据
    virtual HErrorType getData(HActionType action, int &value, int delay = 0) = 0;
    virtual HErrorType getData(HActionType action, uchar &value, int delay = 0) = 0;
    virtual HErrorType getData(HActionType action, uint &value, int delay = 0) = 0;
    virtual HErrorType getData(HActionType action, QVector<int> &value, int delay = 0) = 0;
    virtual HErrorType getData(HActionType action, QVector<uchar> &value, int delay = 0) = 0;
    virtual HErrorType getData(HActionType action, QVector<uint> &value, int delay = 0) = 0;
    virtual HErrorType getData(HActionType action, QVector<double> &value, int delay = 0) = 0;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // IPROTOCOL_H
