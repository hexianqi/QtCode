#ifndef HABSTRACTPROTOCOLSTRATEGY_H
#define HABSTRACTPROTOCOLSTRATEGY_H

#include "IProtocolStrategy.h"
#include <QScopedPointer>

HE_COMMUNICATE_BEGIN_NAMESPACE

class HAbstractProtocolStrategyPrivate;

class HAbstractProtocolStrategy : public IProtocolStrategy
{
public:
    HAbstractProtocolStrategy();
    virtual ~HAbstractProtocolStrategy();

public:
    virtual void initialize(QVariantMap param) override;
    virtual void setPort(IPort *port, int num = 0, bool scan = true) override;
    virtual void setDeviceID(int id) override;
    virtual void addActionParam(HActionType key, QList<uchar> value) override;

public:
    virtual HErrorType open() override;
    virtual HErrorType close() override;

protected:
    HAbstractProtocolStrategy(HAbstractProtocolStrategyPrivate &p);

protected:
    virtual HErrorType openDevice(int num);
    virtual HErrorType checkDevice();

protected:
    QScopedPointer<HAbstractProtocolStrategyPrivate> d_ptr;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HABSTRACTPROTOCOLSTRATEGY_H
