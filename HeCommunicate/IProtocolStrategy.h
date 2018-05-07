#ifndef IPROTOCOLSTRATEGY_H
#define IPROTOCOLSTRATEGY_H

#include "HCommunicateGlobal.h"
#include "HeCore/HActionType.h"
#include "HeCore/HErrorType.h"
#include <QVariant>

HE_CORE_USE_NAMESPACE

HE_COMMUNICATE_BEGIN_NAMESPACE

class IPort;

class HE_COMMUNICATE_EXPORT IProtocolStrategy
{
public:
    virtual void initialize(QVariantMap param) = 0;
    virtual void setPort(IPort *port, int num = 0, bool scan = true) = 0;
    virtual void setDeviceID(int id) = 0;
    virtual void addActionParam(HActionType key, QList<uchar> value) = 0;

public:
    virtual HErrorType open() = 0;
    virtual HErrorType close() = 0;
    virtual HErrorType setData(HActionType action, QVector<uchar> value, int delay = 0) = 0;
    virtual HErrorType getData(HActionType action, QVector<uchar> &value, int delay = 0) = 0;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // IPROTOCOLSTRATEGY_H
