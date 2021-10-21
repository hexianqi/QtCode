/***************************************************************************************************
**      2021-03-09  HAdjustItemCollection
***************************************************************************************************/

#pragma once

#include "IAdjustItemCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HAdjustItemCollectionPrivate;

class HAdjustItemCollection : public IAdjustItemCollection
{
    Q_DECLARE_PRIVATE(HAdjustItemCollection)

public:
    explicit HAdjustItemCollection();
    ~HAdjustItemCollection();

public:
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    void setData(QString name, QVariant value) override;
    QVariant data(QString name) override;

public:
    void restoreDefault() override;
    QVariantMap correct(QVariantMap value) override;

protected:
    HAdjustItemCollection(HAdjustItemCollectionPrivate &);
};

HE_DATA_END_NAMESPACE

