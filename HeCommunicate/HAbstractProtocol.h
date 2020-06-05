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
    QString portType() override;
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
    HAbstractProtocol(HAbstractProtocolPrivate &);

protected:
    virtual QVector<uchar> toVector(int value) = 0;
    virtual QVector<uchar> toVector(uint value) = 0;
    virtual int toInt(QVector<uchar> value) = 0;
    virtual uint toUInt(QVector<uchar> value) = 0;
    virtual QVector<int> toVectorInt(QVector<uchar> value, int size) = 0;
    virtual QVector<uint> toVectorUInt(QVector<uchar> value, int size) = 0;
    virtual QVector<double> toVectorDouble(QVector<uchar> value, int size) = 0;

protected:
    QScopedPointer<HAbstractProtocolPrivate> d_ptr;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HABSTRACTPROTOCOL_H
