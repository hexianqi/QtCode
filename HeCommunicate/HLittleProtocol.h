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
    HLittleProtocol(HLittleProtocolPrivate &);
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HLITTLEPROTOCOL_H
