/***************************************************************************************************
**      2019-05-05  HQualityCollection 品质数据集合类。
***************************************************************************************************/

#pragma once

#include "IQualityCollection.h"

HE_BEGIN_NAMESPACE

class HQualityCollectionPrivate;

class HQualityCollection : public IQualityCollection
{
    Q_DECLARE_PRIVATE(HQualityCollection)

public:
    explicit HQualityCollection();
    ~HQualityCollection();

public:
    QString typeName() override;

public:
    HQualityReport check(QVariantMap value, QVariantMap *color = nullptr) override;
    QColor color(HQualityReport type) override;
    double drift(QString type, QVariant value) override;

protected:
    HQualityCollection(HQualityCollectionPrivate &);
};

HE_END_NAMESPACE
