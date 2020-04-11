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
    Q_DECLARE_PRIVATE(HChromatismItem)

public:
    explicit HChromatismItem();

public:
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    double calcSdcm(QPointF xy) override;

protected:
    HChromatismItem(HChromatismItemPrivate &);
};

HE_DATA_END_NAMESPACE

#endif // HCHROMATISMITEM_H
