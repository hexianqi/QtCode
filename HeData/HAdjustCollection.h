/***************************************************************************************************
**      2019-04-26  HAdjustCollection 调整数据集合类。
***************************************************************************************************/

#pragma once

#include "IAdjustCollection.h"

HE_BEGIN_NAMESPACE

class HAdjustCollectionPrivate;

class HAdjustCollection : public IAdjustCollection
{
    Q_DECLARE_PRIVATE(HAdjustCollection)

public:
    explicit HAdjustCollection();
    ~HAdjustCollection();

public:
    QString typeName() override;

public:
    QVariantMap correct(QVariantMap value) override;

protected:
    HAdjustCollection(HAdjustCollectionPrivate &);
};

HE_END_NAMESPACE
