#ifndef ICOMMUNICATEFACTORY_H
#define ICOMMUNICATEFACTORY_H

#include "HCommunicateGlobal.h"
#include <QVariant>

HE_COMMUNICATE_BEGIN_NAMESPACE

class IPort;
class IDevice;
class IProtocol;

class HE_COMMUNICATE_EXPORT ICommunicateFactory
{
public:
    // 初始化
    virtual void initialize(QVariantMap param) = 0;
    // 创建通讯端口
    virtual IPort *createPort(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建通讯设备
    virtual IDevice *createDevice(QString type, QVariantMap param = QVariantMap()) = 0;
    // 创建通讯协议
    virtual IProtocol *createProtocol(QString type, QVariantMap param = QVariantMap()) = 0;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // ICOMMUNICATEFACTORY_H
