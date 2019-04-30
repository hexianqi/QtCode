/***************************************************************************************************
**      2019-04-28  HAdjustItem 调整数据子项。
***************************************************************************************************/

#ifndef HADJUSTITEM_H
#define HADJUSTITEM_H

#include "IAdjustItem.h"

HE_DATA_BEGIN_NAMESPACE

class HAdjustItemPrivate;

class HAdjustItem : public IAdjustItem
{
public:
    explicit HAdjustItem();
    virtual ~HAdjustItem();

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
    QVariant correct(QVariant value) override;
    QStringList toStringList() override;

protected:
    HAdjustItem(HAdjustItemPrivate &);

protected:
    QScopedPointer<HAdjustItemPrivate> d_ptr;
};

HE_DATA_END_NAMESPACE

#endif // HADJUSTITEM_H
