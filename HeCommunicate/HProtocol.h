/***************************************************************************************************
**      2018-06-19  HProtocol 协议类。
***************************************************************************************************/

#ifndef HPROTOCOL_H
#define HPROTOCOL_H

#include "IProtocol.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HProtocolPrivate;

class HProtocol : public IProtocol
{
public:
    explicit HProtocol();
    ~HProtocol();

public:
    virtual void initialize(QVariantMap param) override;
    virtual QString typeName() override;
    virtual void setDevice(IDevice *device) override;
    virtual HErrorType open() override;
    virtual HErrorType close() override;

public:
    virtual HErrorType setData(HActionType action, int value, int delay = 0) override;
    virtual HErrorType setData(HActionType action, double value, double factor = 1.0, int delay = 0) override;
    virtual HErrorType setData(HActionType action, uchar value, int delay = 0) override;
    virtual HErrorType setData(HActionType action, uint value, int delay = 0) override;
    virtual HErrorType setData(HActionType action, QVector<int> value, int delay = 0) override;
    virtual HErrorType setData(HActionType action, QVector<double> value, double factor = 1.0, int delay = 0) override;
    virtual HErrorType setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    virtual HErrorType setData(HActionType action, QVector<uint> value, int delay = 0) override;

public:
    virtual HErrorType getData(HActionType action, int &value, int delay = 0) override;
    virtual HErrorType getData(HActionType action, double &value, double factor = 1.0, int delay = 0) override;
    virtual HErrorType getData(HActionType action, uchar &value, int delay = 0) override;
    virtual HErrorType getData(HActionType action, uint &value, int delay = 0) override;
    virtual HErrorType getData(HActionType action, QVector<int> &value, int delay = 0) override;
    virtual HErrorType getData(HActionType action, QVector<double> &value, double factor = 1.0, int delay = 0) override;
    virtual HErrorType getData(HActionType action, QVector<uchar> &value, int delay = 0) override;
    virtual HErrorType getData(HActionType action, QVector<uint> &value, int delay = 0) override;

protected:
    HProtocol(HProtocolPrivate &p);

protected:
    QScopedPointer<HProtocolPrivate> d_ptr;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HPROTOCOL_H
