/***************************************************************************************************
**      2019-05-06  HQualityItem 品质数据项。
***************************************************************************************************/

#ifndef HQUALITYITEM_H
#define HQUALITYITEM_H

#include "IQualityItem.h"

HE_DATA_BEGIN_NAMESPACE

class HQualityItemPrivate;

class HQualityItem : public IQualityItem
{
public:
    explicit HQualityItem();
    virtual ~HQualityItem();

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void setData(QString name, QVariant value) override;
    void setData(QVariantMap value) override;
    QVariant data(QString name) override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    void restoreDefault() override;
    bool isContains(QVariant value, QColor *color) override;
    double drift(QVariant value) override;
    QStringList toStringList() override;

protected:
    HQualityItem(HQualityItemPrivate &);

protected:
    QScopedPointer<HQualityItemPrivate> d_ptr;
};

HE_DATA_END_NAMESPACE

#endif // HQUALITYITEM_H
