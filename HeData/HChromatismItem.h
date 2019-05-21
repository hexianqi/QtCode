/***************************************************************************************************
**      2019-05-20  HChromatismItem 色容差数据项。
***************************************************************************************************/

#ifndef HCHROMATISMITEM_H
#define HCHROMATISMITEM_H

#include "IChromatismItem.h"

HE_DATA_BEGIN_NAMESPACE

class HChromatismItemPrivate;

class HChromatismItem : public IChromatismItem
{
public:
    explicit HChromatismItem();
    virtual ~HChromatismItem();

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
    double calcSdcm(QPointF xy) override;
    QJsonObject toJson() override;

protected:
    HChromatismItem(HChromatismItemPrivate &);

protected:
    QScopedPointer<HChromatismItemPrivate> d_ptr;
};

HE_DATA_END_NAMESPACE

#endif // HCHROMATISMITEM_H
