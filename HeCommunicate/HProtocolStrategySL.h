#ifndef HPROTOCOLSTRATEGYSL_H
#define HPROTOCOLSTRATEGYSL_H

#include "HAbstractProtocolStrategy.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HProtocolStrategySLPrivate;

class HProtocolStrategySL : public HAbstractProtocolStrategy
{
    Q_DECLARE_PRIVATE(HProtocolStrategySL)

public:
    HProtocolStrategySL();
    ~HProtocolStrategySL();

public:
    virtual void initialize(QVariantMap param) override;
    virtual void setEncrypt(QVector<bool> value);
    virtual void setCheckCode(QVector<bool> value);
    virtual HErrorType setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    virtual HErrorType getData(HActionType action, QVector<uchar> &value, int delay = 0) override;

protected:
    HProtocolStrategySL(HProtocolStrategySLPrivate &p);

protected:
    virtual HErrorType transport(QVector<uchar> &downData, QVector<uchar> &upData, int delay = 0);
    virtual QVector<uchar> encrypt(QVector<uchar> value, int size);
    virtual QVector<uchar> decrypt(QVector<uchar> value, int size);
    virtual uchar calcCode(QVector<uchar> value);
    virtual bool checkCode(QVector<uchar> value, uchar code);
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HPROTOCOLSTRATEGYSL_H
