/***************************************************************************************************
**      2020-05-22  HLuminousCalibrateItem
***************************************************************************************************/

#pragma once

#include "ILuminousCalibrateItem.h"
#include "HAbstractDataItem.h"

HE_BEGIN_NAMESPACE

class HLuminousCalibrateItemPrivate;

class HLuminousCalibrateItem : public HAbstractDataItem, public virtual ILuminousCalibrateItem
{
    Q_DECLARE_PRIVATE(HLuminousCalibrateItem)

public:
    explicit HLuminousCalibrateItem();
    ~HLuminousCalibrateItem();

public:
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    void setTotalGears(int value) override;
    int totalGears() override;
    void setRelation(int index, QPolygonF value) override;
    QPolygonF relation(int index) override;
    double toReal(double value, int index) override;

protected:
    HLuminousCalibrateItem(HLuminousCalibrateItemPrivate &);
};

HE_END_NAMESPACE

