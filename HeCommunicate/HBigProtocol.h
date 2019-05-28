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

public:
    HErrorType setData(HActionType action, int value, int delay = 0) override;
    HErrorType setData(HActionType action, uchar value, int delay = 0) override;
    HErrorType setData(HActionType action, uint value, int delay = 0) override;
    HErrorType setData(HActionType action, QVector<uchar> value, int delay = 0) override;
    HErrorType setData(HActionType action, QVector<int> value, int delay = 0) override;
    HErrorType setData(HActionType action, QVector<uint> value, int delay = 0) override;

public:
    HErrorType getData(HActionType action, int &value, int delay = 0) override;
    HErrorType getData(HActionType action, uchar &value, int delay = 0) override;
    HErrorType getData(HActionType action, uint &value, int delay = 0) override;
    HErrorType getData(HActionType action, QVector<uchar> &value, int delay = 0) override;
    HErrorType getData(HActionType action, QVector<int> &value, int delay = 0) override;
    HErrorType getData(HActionType action, QVector<uint> &value, int delay = 0) override;
    HErrorType getData(HActionType action, QVector<double> &value, int delay = 0) override;

protected:
    HBigProtocol(HBigProtocolPrivate &);
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HBIGPROTOCOL_H
