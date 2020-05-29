/***************************************************************************************************
**      2020-05-22  HLuminousCalibrateItem
***************************************************************************************************/

#pragma once

#include "ILuminousCalibrateItem.h"

HE_DATA_BEGIN_NAMESPACE

class HLuminousCalibrateItemPrivate;

class HLuminousCalibrateItem : public ILuminousCalibrateItem
{
    Q_DECLARE_PRIVATE(HLuminousCalibrateItem)

public:
    explicit HLuminousCalibrateItem();
    ~HLuminousCalibrateItem() = default;

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

HE_DATA_END_NAMESPACE

