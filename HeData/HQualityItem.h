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
    Q_DECLARE_PRIVATE(HQualityItem)

public:
    explicit HQualityItem();
    ~HQualityItem() override;

public:
    QString typeName() override;

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
};

HE_DATA_END_NAMESPACE

#endif // HQUALITYITEM_H
