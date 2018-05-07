#ifndef IPROTOCOLINFO_H
#define IPROTOCOLINFO_H

#include "HCommunicateGlobal.h"
#include "HeCore/HActionType.h"
#include <QVariant>

HE_CORE_USE_NAMESPACE

HE_COMMUNICATE_BEGIN_NAMESPACE

class IPort;

class HE_COMMUNICATE_EXPORT IProtocolInfo
{
public:
    virtual void initialize(QVariantMap param) = 0;
    virtual void setPort(IPort *port, int num = 0, bool scan = true) = 0;
    virtual void setPortNum(int num) = 0;
    virtual void setDeviceID(int id) = 0;
    virtual void addActionParam(HActionType key, QList<uchar> value) = 0;

public:
    virtual IPort *port() = 0;
    virtual int portNum() = 0;
    virtual bool isPortNumScan() = 0;
    virtual int deviceID() = 0;
    virtual QList<uchar> actionParam(HActionType key) = 0;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // IPROTOCOLINFO_H
