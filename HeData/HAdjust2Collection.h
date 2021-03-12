/***************************************************************************************************
**      2021-03-09  HAdjust2Collection
***************************************************************************************************/

#pragma once

#include "IAdjust2Collection.h"

HE_DATA_BEGIN_NAMESPACE

class HAdjust2CollectionPrivate;

class HAdjust2Collection : public IAdjust2Collection
{
    Q_DECLARE_PRIVATE(HAdjust2Collection)

public:
    explicit HAdjust2Collection();
    virtual ~HAdjust2Collection() = default;

public:
    QString typeName() override;

public:
    QVariantMap correct(double tc, QVariantMap value) override;

protected:
    HAdjust2Collection(HAdjust2CollectionPrivate &);
};

HE_DATA_END_NAMESPACE

