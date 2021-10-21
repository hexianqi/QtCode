/***************************************************************************************************
**      2018-06-19  HCommunicateFactory 通讯器工厂接口。
***************************************************************************************************/

#pragma once

#include "HCommunicateGlobal.h"
#include "HeCore/IInitializeable.h"

HE_CORE_USE_NAMESPACE

HE_COMMUNICATE_BEGIN_NAMESPACE

class IPort;
class IDevice;
class IProtocol;
class IProtocolCollection;

class ICommunicateFactory : public IInitializeable
{
public:
    // 创建通讯端口
    virtual IPort *createPort(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建通讯设备
    virtual IDevice *createDevice(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建通讯协议
    virtual IProtocol *createProtocol(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建通讯协议集合
    virtual IProtocolCollection *createProtocolCollection(QString type, QVariantMap param = QVariantMap()) = 0;
};

HE_COMMUNICATE_END_NAMESPACE
