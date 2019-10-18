/***************************************************************************************************
**      2019-05-06  HQualityItemCollection 品质数据项集合。
***************************************************************************************************/

#ifndef HQUALITYITEMCOLLECTION_H
#define HQUALITYITEMCOLLECTION_H

#include "IQualityItemCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HQualityItemCollectionPrivate;

class HQualityItemCollection : public IQualityItemCollection
{
    Q_DECLARE_PRIVATE(HQualityItemCollection)

public:
    explicit HQualityItemCollection();
    virtual ~HQualityItemCollection();

public:
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    int check(QVariantMap value, QVariantMap *color) override;
    double drift(QString type, QVariant value) override;

protected:
    HQualityItemCollection(HQualityItemCollectionPrivate &);
};

HE_DATA_END_NAMESPACE

#endif // HQUALITYITEMCOLLECTION_H
