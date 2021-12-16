/***************************************************************************************************
**      2019-05-20  HChromatismCollection 色容差数据集合。
***************************************************************************************************/

#pragma once

#include "IChromatismCollection.h"

HE_BEGIN_NAMESPACE

class HChromatismCollectionPrivate;

class HChromatismCollection : public IChromatismCollection
{
    Q_DECLARE_PRIVATE(HChromatismCollection)

public:
    explicit HChromatismCollection();
    ~HChromatismCollection();

public:
    QString typeName() override;

public:
    double calcSdcm(double tc, QPointF xy) override;
    QVariantMap toMap() override;

protected:
    HChromatismCollection(HChromatismCollectionPrivate &);
};

HE_END_NAMESPACE
