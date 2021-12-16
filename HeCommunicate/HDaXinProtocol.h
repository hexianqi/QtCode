/***************************************************************************************************
**      2021-01-18  HDaXinProtocol
***************************************************************************************************/

#pragma once

#include "HBigProtocol.h"

HE_BEGIN_NAMESPACE

class HDaXinProtocolPrivate;

class HDaXinProtocol : public HBigProtocol
{
    Q_DECLARE_PRIVATE(HDaXinProtocol)

public:
    explicit HDaXinProtocol();
    ~HDaXinProtocol() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;

protected:
    HDaXinProtocol(HDaXinProtocolPrivate &);
};

HE_END_NAMESPACE

