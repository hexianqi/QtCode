/***************************************************************************************************
**      2019-05-27  HUi2010Protocol UI2010协议。
***************************************************************************************************/

#pragma once

#include "HLittleProtocol.h"

HE_BEGIN_NAMESPACE

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

HE_END_NAMESPACE
