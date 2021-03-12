/***************************************************************************************************
**      2018-06-19  HLittleProtocol 低位编址协议类（低字节在前）。
***************************************************************************************************/

#pragma once

#include "HAbstractProtocol.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HLittleProtocolPrivate;

class HLittleProtocol : public HAbstractProtocol
{
    Q_DECLARE_PRIVATE(HLittleProtocol)

public:
    explicit HLittleProtocol();
    ~HLittleProtocol() override;

public:
    QString typeName() override;

protected:
    HLittleProtocol(HLittleProtocolPrivate &);

protected:
    QVector<uchar> toVector(int value) override;
    QVector<uchar> toVector(uint value) override;
    QVector<uchar> toVector(double value) override;
    int toInt(QVector<uchar> value) override;
    uint toUInt(QVector<uchar> value) override;
    QVector<int> toInt(QVector<uchar> value, int size) override;
    QVector<uint> toUInt(QVector<uchar> value, int size) override;
    QVector<double> toDouble(QVector<uchar> value, int size) override;
};

HE_COMMUNICATE_END_NAMESPACE
