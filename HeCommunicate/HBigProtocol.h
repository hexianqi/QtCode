/***************************************************************************************************
**      2019-05-28  HBigProtocol 高位编址协议类（高字节在前）。
***************************************************************************************************/

#ifndef HBIGPROTOCOL_H
#define HBIGPROTOCOL_H

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
    int toInt(QVector<uchar> value) override;
    uint toUInt(QVector<uchar> value) override;
    QVector<int> toVectorInt(QVector<uchar> value, int size) override;
    QVector<uint> toVectorUInt(QVector<uchar> value, int size) override;
    QVector<double> toVectorDouble(QVector<uchar> value, int size) override;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HBIGPROTOCOL_H
