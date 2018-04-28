#ifndef IPROTOCOL_H
#define IPROTOCOL_H

#include "HCommunicateGlobal.h"
#include "HeCore/HErrorType.h"
#include "HeCore/HActionType.h"
#include <QVariant>

HE_CORE_USE_NAMESPACE

HE_COMMUNICATE_BEGIN_NAMESPACE

class IPort;

class HE_COMMUNICATE_EXPORT IProtocol
{
public:
    virtual void initialize(QVariantMap param) = 0;
    virtual void setPort(IPort *port) = 0;
    virtual HErrorType setData(HActionType action, int value, int delay = 0) = 0;
    virtual HErrorType setData(HActionType action, quint32 value, int delay = 0) = 0;
    virtual HErrorType setData(HActionType action, QVector<uchar> value, int delay = 0) = 0;
    virtual HErrorType setData(HActionType action, QVector<quint32> value, int delay = 0) = 0;
    virtual HErrorType setData(HActionType action, QVector<int> value, int delay = 0) = 0;
    virtual HErrorType setData(HActionType action, QVector<double> value, int delay = 0) = 0;
    virtual HErrorType getData(HActionType action, int &value, int delay = 10) = 0;
    virtual HErrorType getData(HActionType action, QVector<uchar> &value, int delay = 10) = 0;
    virtual HErrorType getData(HActionType action, QVector<int> &value, int delay = 10) = 0;
    virtual HErrorType getData(HActionType action, QVector<double> &value, int delay = 10) = 0;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // IPROTOCOL_H
