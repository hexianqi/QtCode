/***************************************************************************************************
**      2019-10-17  HElecCalibrateItem 电参数校准子项。
***************************************************************************************************/

#pragma once

#include "IElecCalibrateItem.h"

HE_DATA_BEGIN_NAMESPACE

class HElecCalibrateItemPrivate;

class HElecCalibrateItem : public IElecCalibrateItem
{
    Q_DECLARE_PRIVATE(HElecCalibrateItem)

public:
    explicit HElecCalibrateItem();

public:
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

public:
    void restoreDefault() override;
    void setRelation(QPolygonF value) override;
    QPolygonF relation() override;
    double toFiction(double value) override;
    double toReal(double value) override;

protected:
    HElecCalibrateItem(HElecCalibrateItemPrivate &);
};

HE_DATA_END_NAMESPACE
