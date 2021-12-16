/***************************************************************************************************
**      2019-05-20  HChromatismItem 色容差数据项。
***************************************************************************************************/

#pragma once

#include "IChromatismItem.h"
#include "HAbstractDataItem.h"

HE_BEGIN_NAMESPACE

class HChromatismItemPrivate;

class HChromatismItem : public HAbstractDataItem, public virtual IChromatismItem
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

HE_END_NAMESPACE
