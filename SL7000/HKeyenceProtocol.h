/***************************************************************************************************
**      2022-02-08  HKeyenceProtocol
***************************************************************************************************/

#pragma once

#include "HeCommunicate/HBigProtocol.h"

HE_USE_NAMESPACE

class HKeyenceProtocolPrivate;

class HKeyenceProtocol : public HBigProtocol
{
    Q_DECLARE_PRIVATE(HKeyenceProtocol)

public:
    explicit HKeyenceProtocol();
    ~HKeyenceProtocol() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

protected:
    HKeyenceProtocol(HKeyenceProtocolPrivate &);
};



