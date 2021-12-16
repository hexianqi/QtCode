/***************************************************************************************************
**      2021-03-09  HAdjust2Collection
***************************************************************************************************/

#pragma once

#include "IAdjust2Collection.h"

HE_BEGIN_NAMESPACE

class HAdjust2CollectionPrivate;

class HAdjust2Collection : public IAdjust2Collection
{
    Q_DECLARE_PRIVATE(HAdjust2Collection)

public:
    explicit HAdjust2Collection();
    ~HAdjust2Collection();

public:
    QString typeName() override;

public:
    QVariantMap correct(double tc, QVariantMap value) override;

protected:
    HAdjust2Collection(HAdjust2CollectionPrivate &);
};

HE_END_NAMESPACE

