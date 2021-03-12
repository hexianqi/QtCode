/***************************************************************************************************
**      2018-06-19  HProtocolCollection 协议集合类。
***************************************************************************************************/

#pragma once

#include "IProtocolCollection.h"

HE_COMMUNICATE_BEGIN_NAMESPACE

class HProtocolCollectionPrivate;

class HProtocolCollection : public IProtocolCollection
{
    Q_DECLARE_PRIVATE(HProtocolCollection)

public:
    explicit HProtocolCollection();
    virtual ~HProtocolCollection();

public:
    QString typeName() override;

protected:
    HProtocolCollection(HProtocolCollectionPrivate &);
};

HE_COMMUNICATE_END_NAMESPACE
