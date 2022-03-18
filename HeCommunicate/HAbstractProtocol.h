/***************************************************************************************************
**      2019-05-28  HAbstractProtocol 抽象协议类。
***************************************************************************************************/

#pragma once

#include "IProtocol.h"

HE_BEGIN_NAMESPACE

class HAbstractProtocolPrivate;

class HAbstractProtocol : public IProtocol
{
public:
    explicit HAbstractProtocol();
    virtual ~HAbstractProtocol();

public:
    void initialize(QVariantMap param = QVariantMap()) override;

public:
    QString portType() override;
    void setDevice(IDevice *) override;
    bool open() override;
    bool close() override;

public:
    bool setData(HActionType action) override;
    bool setData(HActionType action, int value, int delay = 0) override;
    bool setData(HActionType action, uchar value, int delay = 0) override;
    bool setData(HActionType action, uint value, int delay = 0) override;
    bool setData(HActionType action, double value, int delay = 0) override;
    bool setData(HActionType action, QVector<int> value, int delay = 0) override;
    bool setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    bool setData(HActionType action, QVector<uint> value, int delay = 0) override;
    bool setData(HActionType action, QVector<double> value, int delay = 0) override;

public:
    bool getData(HActionType action) override;
    bool getData(HActionType action, int &value, int delay = 0) override;
    bool getData(HActionType action, uchar &value, int delay = 0) override;
    bool getData(HActionType action, uint &value, int delay = 0) override;
    bool getData(HActionType action, QVector<int> &value, int delay = 0) override;
    bool getData(HActionType action, QVector<uchar> &value, int delay = 0) override;
    bool getData(HActionType action, QVector<uint> &value, int delay = 0) override;
    bool getData(HActionType action, QVector<double> &value, int delay = 0) override;

protected:
    HAbstractProtocol(HAbstractProtocolPrivate &);

protected:
    virtual QVector<uchar> toVector(int value) = 0;
    virtual QVector<uchar> toVector(uint value) = 0;
    virtual QVector<uchar> toVector(double value) = 0;
    virtual int toInt(QVector<uchar> value) = 0;
    virtual uint toUInt(QVector<uchar> value) = 0;
    virtual QVector<int> toInt(QVector<uchar> value, int size) = 0;
    virtual QVector<uint> toUInt(QVector<uchar> value, int size) = 0;
    virtual QVector<double> toDouble(QVector<uchar> value, int size) = 0;

protected:
    QScopedPointer<HAbstractProtocolPrivate> d_ptr;
};

HE_END_NAMESPACE
