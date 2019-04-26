/***************************************************************************************************
**      2019-04-16  HGradeCollection 分级数据集合类。
***************************************************************************************************/

#ifndef HGRADECOLLECTION_H
#define HGRADECOLLECTION_H

#include "IGradeCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HGradeCollectionPrivate;

class HGradeCollection : public IGradeCollection
{
    Q_DECLARE_PRIVATE(HGradeCollection)

public:
    explicit HGradeCollection(IDataFactory *);
    virtual ~HGradeCollection();

public:
    QString typeName() override;

public:
    IDataFactory *dataFactory() override;
    IFileStream *fileStream() override;
    void setUseIndex(QString value) override;
    QString useIndex() override;

public:
    QVariant levels(QString type) override;
    int calcLevel(QVariantMap value, QString &text) override;

protected:
    HGradeCollection(HGradeCollectionPrivate &);
};

HE_DATA_END_NAMESPACE

#endif // HGRADECOLLECTION_H
