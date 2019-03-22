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
    virtual ~HProtocol();

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void setDevice(IDevice *) override;
    HErrorType open() override;
    HErrorType close() override;

public:
    HErrorType setData(HActionType action, int value, int delay = 0) override;
    HErrorType setData(HActionType action, uchar value, int delay = 0) override;
    HErrorType setData(HActionType action, uint value, int delay = 0) override;
    HErrorType setData(HActionType action, QVector<int> value, int delay = 0) override;
    HErrorType setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    HErrorType setData(HActionType action, QVector<uint> value, int delay = 0) override;

public:
    HErrorType getData(HActionType action, int &value, int delay = 0) override;
    HErrorType getData(HActionType action, uchar &value, int delay = 0) override;
    HErrorType getData(HActionType action, uint &value, int delay = 0) override;
    HErrorType getData(HActionType action, QVector<int> &value, int delay = 0) override;
    HErrorType getData(HActionType action, QVector<uchar> &value, int delay = 0) override;
    HErrorType getData(HActionType action, QVector<uint> &value, int delay = 0) override;
    HErrorType getData(HActionType action, QVector<double> &value, int delay = 0) override;

protected:
    HProtocol(HProtocolPrivate &);

protected:
    QScopedPointer<HProtocolPrivate> d_ptr;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HPROTOCOL_H
