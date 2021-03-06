/***************************************************************************************************
**      2019-04-18  HGradeItem 分级数据项。
***************************************************************************************************/

#ifndef HGRADEITEM_H
#define HGRADEITEM_H

#include "HAbstractGradeItem.h"

HE_DATA_BEGIN_NAMESPACE

class HGradeItemPrivate;

class HGradeItem : public HAbstractGradeItem
{
    Q_DECLARE_PRIVATE(HGradeItem)

public:
    explicit HGradeItem();
    ~HGradeItem() override;

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
};

HE_DATA_END_NAMESPACE

#endif // HGRADEITEM_H
