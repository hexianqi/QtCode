/***************************************************************************************************
**      2019-04-28  HAdjustItem 调整数据项。
***************************************************************************************************/

#ifndef HADJUSTITEM_H
#define HADJUSTITEM_H

#include "IAdjustItem.h"

HE_DATA_BEGIN_NAMESPACE

class HAdjustItemPrivate;

class HAdjustItem : public IAdjustItem
{
    Q_DECLARE_PRIVATE(HAdjustItem)

public:
    explicit HAdjustItem();
    ~HAdjustItem() override;

public:
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    void restoreDefault() override;
    QVariant correct(QVariant value) override;
    QStringList toStringList() override;

protected:
    HAdjustItem(HAdjustItemPrivate &);
};

HE_DATA_END_NAMESPACE

#endif // HADJUSTITEM_H
