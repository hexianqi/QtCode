#ifndef IPROTOCOL_H
#define IPROTOCOL_H

#include "HCommunicateGlobal.h"
#include "HeCore/HErrorType.h"
#include "HeCore/HActionType.h"
#include <QVariant>

HE_CORE_USE_NAMESPACE

HE_COMMUNICATE_BEGIN_NAMESPACE

class IProtocolStrategy;

class HE_COMMUNICATE_EXPORT IProtocol
{
public:
    virtual void initialize(QVariantMap param) = 0;
    virtual void setStrategy(IProtocolStrategy *strategy) = 0;
    virtual HErrorType open() = 0;
    virtual HErrorType close() = 0;
    virtual QString objectName() = 0;

public:
    virtual HErrorType setData(HActionType action, int value, int delay = 0) = 0;
    virtual HErrorType setData(HActionType action, double value, double factor = 1.0, int delay = 0) = 0;
    virtual HErrorType setData(HActionType action, uchar value, int delay = 0) = 0;
    virtual HErrorType setData(HActionType action, uint value, int delay = 0) = 0;
    virtual HErrorType setData(HActionType action, QVector<int> value, int delay = 0) = 0;
    virtual HErrorType setData(HActionType action, QVector<double> value, double factor = 1.0, int delay = 0) = 0;
    virtual HErrorType setData(HActionType action, QVector<uchar> value, int delay = 0) = 0;
    virtual HErrorType setData(HActionType action, QVector<uint> value, int delay = 0) = 0;

public:
    virtual HErrorType getData(HActionType action, int &value, int delay = 0) = 0;
    virtual HErrorType getData(HActionType action, double &value, double factor = 1.0, int delay = 0) = 0;
    virtual HErrorType getData(HActionType action, uchar &value, int delay = 0) = 0;
    virtual HErrorType getData(HActionType action, uint &value, int delay = 0) = 0;
    virtual HErrorType getData(HActionType action, QVector<int> &value, int delay = 0) = 0;
    virtual HErrorType getData(HActionType action, QVector<double> &value, double factor = 1.0, int delay = 0) = 0;
    virtual HErrorType getData(HActionType action, QVector<uchar> &value, int delay = 0) = 0;
    virtual HErrorType getData(HActionType action, QVector<uint> &value, int delay = 0) = 0;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // IPROTOCOL_H
