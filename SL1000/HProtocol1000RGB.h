/***************************************************************************************************
**      2022-12-06  HProtocol1000RGB
***************************************************************************************************/

#pragma once

#include "HeCommunicate/HAbstractProtocol.h"

HE_USE_NAMESPACE

class HProtocol1000RGBPrivate;

class HProtocol1000RGB : public HAbstractProtocol
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(HProtocol1000RGB)

public:
    explicit HProtocol1000RGB(QObject *parent = nullptr);
    ~HProtocol1000RGB() override;

public:
    QString typeName() override;

protected:
    virtual void init();
};



