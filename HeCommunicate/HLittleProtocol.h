/***************************************************************************************************
**      2018-06-19  HLittleProtocol 低位编址协议类（低字节在前）。
***************************************************************************************************/

#ifndef HLITTLEPROTOCOL_H
#define HLITTLEPROTOCOL_H

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
    int toInt(QVector<uchar> value) override;
    uint toUInt(QVector<uchar> value) override;
    QVector<int> toVectorInt(QVector<uchar> value, int size) override;
    QVector<uint> toVectorUInt(QVector<uchar> value, int size) override;
    QVector<double> toVectorDouble(QVector<uchar> value, int size) override;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HLITTLEPROTOCOL_H
