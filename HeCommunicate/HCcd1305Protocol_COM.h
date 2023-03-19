/***************************************************************************************************
**      2023-03-11  HCcd1305Protocol_COM
***************************************************************************************************/

#pragma once

#include "HBigProtocol.h"

HE_BEGIN_NAMESPACE

class HCcd1305Protocol_COMPrivate;

class HCcd1305Protocol_COM : public HBigProtocol
{
    Q_DECLARE_PRIVATE(HCcd1305Protocol_COM)

public:
    explicit HCcd1305Protocol_COM();
    ~HCcd1305Protocol_COM() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

protected:
    HCcd1305Protocol_COM(HCcd1305Protocol_COMPrivate &);
};

HE_END_NAMESPACE

