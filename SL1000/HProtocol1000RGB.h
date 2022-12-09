/***************************************************************************************************
**      2022-12-06  HProtocol1000RGB
***************************************************************************************************/

#pragma once

#include "HeCommunicate/HLittleProtocol.h"

HE_USE_NAMESPACE

class HProtocol1000RGBPrivate;

class HProtocol1000RGB : public HLittleProtocol
{
    Q_DECLARE_PRIVATE(HProtocol1000RGB)

public:
    explicit HProtocol1000RGB();
    ~HProtocol1000RGB() override;

public:
    void initialize(QVariantMap param = QVariantMap()) override;
    QString typeName() override;
};



