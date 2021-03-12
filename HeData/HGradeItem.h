/***************************************************************************************************
**      2019-04-18  HGradeItem 分级数据项。
***************************************************************************************************/

#pragma once

#include "IGradeItem.h"

HE_DATA_BEGIN_NAMESPACE

class HGradeItemPrivate;

class HGradeItem : public IGradeItem
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

HE_DATA_END_NAMESPACE
