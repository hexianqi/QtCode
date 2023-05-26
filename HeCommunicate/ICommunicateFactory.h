/***************************************************************************************************
**      2018-06-19  ICommunicateFactory 通讯器工厂接口。
***************************************************************************************************/

#pragma once

#include "HeCore/IInitializeable.h"

HE_BEGIN_NAMESPACE

class IDevice;
class IPort;
class IProtocol;
class IProtocolCollection;
class IUCharConvert;

class ICommunicateFactory : public IInitializeable
{
public:
    // 创建uchar转换器
    virtual IUCharConvert *createUCharConvert(QString type, QObject *parent = nullptr, QVariantMap param = QVariantMap()) = 0;
    // 创建通讯端口
    virtual IPort *createPort(QString type, QObject *parent = nullptr, QVariantMap param = QVariantMap()) = 0;
    // 创建通讯设备
    virtual IDevice *createDevice(QString type, QObject *parent = nullptr, QVariantMap param = QVariantMap()) = 0;
    // 创建通讯协议
    virtual IProtocol *createProtocol(QString type, QObject *parent = nullptr, QVariantMap param = QVariantMap()) = 0;
    // 创建通讯协议集合
    virtual IProtocolCollection *createProtocolCollection(QString type, QVariantMap param = QVariantMap()) = 0;
};

HE_END_NAMESPACE
