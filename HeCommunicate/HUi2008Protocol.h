/***************************************************************************************************
**      2019-05-27  HUi2008Protocol UI2008协议。
***************************************************************************************************/

#pragma once

#include "HLittleProtocol.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HUi2008ProtocolPrivate;

class HUi2008Protocol : public HLittleProtocol
{
    Q_DECLARE_PRIVATE(HUi2008Protocol)

public:
    explicit HUi2008Protocol();
    ~HUi2008Protocol() override;

public:
    QString typeName() override;

public:
    bool getData(HActionType action, QVector<double> &value, int delay = 0) override;
};

HE_COMMUNICATE_END_NAMESPACE
