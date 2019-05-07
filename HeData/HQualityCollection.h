/***************************************************************************************************
**      2019-05-05  HQualityCollection 品质数据集合类。
***************************************************************************************************/

#ifndef HQUALITYCOLLECTION_H
#define HQUALITYCOLLECTION_H

#include "IQualityCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HQualityCollectionPrivate;

class HQualityCollection : public IQualityCollection
{
    Q_DECLARE_PRIVATE(HQualityCollection)

public:
    explicit HQualityCollection(IDataFactory *);
    virtual ~HQualityCollection();

public:
    QString typeName() override;

public:
    IFileStream *fileStream() override;
    void setUseIndex(QString value) override;
    QString useIndex() override;

public:
    HQualityReport check(QVariantMap value, QVariantMap *color = nullptr) override;
    QColor color(HQualityReport value) override;
    double drift(QString type, QVariant value) override;

protected:
    HQualityCollection(HQualityCollectionPrivate &);
};

HE_DATA_END_NAMESPACE

#endif // HQUALITYCOLLECTION_H
