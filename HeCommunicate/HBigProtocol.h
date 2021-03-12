/***************************************************************************************************
**      2019-05-28  HBigProtocol 高位编址协议类（高字节在前）。
***************************************************************************************************/

#pragma once

#include "HAbstractProtocol.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HBigProtocolPrivate;

class HBigProtocol : public HAbstractProtocol
{
    Q_DECLARE_PRIVATE(HBigProtocol)

public:
    explicit HBigProtocol();
    ~HBigProtocol() override;

public:
    QString typeName() override;

protected:
    HBigProtocol(HBigProtocolPrivate &);

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
