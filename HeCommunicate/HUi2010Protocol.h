/***************************************************************************************************
**      2019-05-27  HUi2010Protocol UI2010协议。
***************************************************************************************************/

#ifndef HUI2010PROTOCOL_H
#define HUI2010PROTOCOL_H

#include "HLittleProtocol.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HUi2010ProtocolPrivate;

class HUi2010Protocol : HLittleProtocol
{
    Q_DECLARE_PRIVATE(HUi2010Protocol)

public:
    explicit HUi2010Protocol();
    ~HUi2010Protocol() override;

public:
    QString typeName() override;

public:
    bool getData(HActionType action, QVector<double> &value, int delay = 0) override;
};

HE_COMMUNICATE_END_NAMESPACE

#endif // HUI2010PROTOCOL_H
