/***************************************************************************************************
**      2019-05-28  HAbstractProtocol 抽象协议类。
***************************************************************************************************/

#ifndef HABSTRACTPROTOCOL_H
#define HABSTRACTPROTOCOL_H

#include "IProtocol.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HAbstractProtocolPrivate;

class HAbstractProtocol : public IProtocol
{
public:
    explicit HAbstractProtocol();
    virtual ~HAbstractProtocol();

public:
    void initialize(QVariantMap param) override;

public:
    void setDevice(IDevice *) override;
    HErrorType open() override;
    HErrorType close() final;

public:
    HErrorType setData(HActionType action, uchar value, int delay = 0) override;
    HErrorType setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    HErrorType getData(HActionType action, uchar &value, int delay = 0) override;
    HErrorType getData(HActionType action, QVector<uchar> &value, int delay = 0) override;

protected:
    HAbstractProtocol(HAbstractProtocolPrivate &);

protected:
    QScopedPointer<HAbstractProtocolPrivate> d_ptr;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HABSTRACTPROTOCOL_H
