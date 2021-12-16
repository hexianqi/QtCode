/***************************************************************************************************
**      2019-04-16  HGradeCollection 分级数据集合类。
***************************************************************************************************/

#pragma once

#include "IGradeCollection.h"

HE_BEGIN_NAMESPACE

class HGradeCollectionPrivate;

class HGradeCollection : public IGradeCollection
{
    Q_DECLARE_PRIVATE(HGradeCollection)

public:
    explicit HGradeCollection();
    ~HGradeCollection();

public:
    QString typeName() override;

public:
    QVariant levels(QString type) override;
    int calcLevel(QVariantMap value, QString *text = nullptr) override;

protected:
    HGradeCollection(HGradeCollectionPrivate &);
};

HE_END_NAMESPACE
