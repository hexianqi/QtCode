/***************************************************************************************************
**      2019-04-18  HGradeItem 分级数据项。
***************************************************************************************************/

#pragma once

#include "IGradeItem.h"
#include "HAbstractDataItem.h"

HE_BEGIN_NAMESPACE

class HGradeItemPrivate;

class HGradeItem : public HAbstractDataItem, public virtual IGradeItem
{
    Q_DECLARE_PRIVATE(HGradeItem)

public:
    explicit HGradeItem();

public:
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    void setLevels(QVariant value) override;
    QVariant levels() override;
    QSet<int> indexOf(QVariant value) override;
    int count() override;
    QStringList headers() override;
    QStringList types() override;
    QStringList level(int i) override;

protected:
    HGradeItem(HGradeItemPrivate &);
};

HE_END_NAMESPACE
