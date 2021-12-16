/***************************************************************************************************
**      2019-05-06  HQualityItemCollection 品质数据项集合。
***************************************************************************************************/

#pragma once

#include "IQualityItemCollection.h"

HE_BEGIN_NAMESPACE

class HQualityItemCollectionPrivate;

class HQualityItemCollection : public IQualityItemCollection
{
    Q_DECLARE_PRIVATE(HQualityItemCollection)

public:
    explicit HQualityItemCollection();
    ~HQualityItemCollection();

public:
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    bool isValid(QVariantMap value) override;
    bool check(QVariantMap value, QVariantMap *color) override;
    double drift(QString type, QVariant value) override;

protected:
    HQualityItemCollection(HQualityItemCollectionPrivate &);
};

HE_END_NAMESPACE
