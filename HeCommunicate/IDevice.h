/***************************************************************************************************
**      2018-06-19  IDevice 设备接口。
***************************************************************************************************/

#ifndef IDEVICE_H
#define IDEVICE_H

#include "HCommunicateGlobal.h"
#include "HeCore/IInitializeable.h"
#include "HeCore/HActionType.h"
#include "HeCore/HErrorType.h"

HE_CORE_USE_NAMESPACE

HE_COMMUNICATE_BEGIN_NAMESPACE

class IPort;

class IDevice : public IInitializeable
{
public:
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
    virtual HErrorType open() = 0;
    // 关闭
    virtual HErrorType close() = 0;
    // 设置数据
    virtual HErrorType setData(HActionType action, QVector<uchar> value, int delay = 0) = 0;
    // 获取数据
    virtual HErrorType getData(HActionType action, QVector<uchar> &value, int delay = 0) = 0;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // IDEVICE_H
