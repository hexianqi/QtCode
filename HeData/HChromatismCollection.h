/***************************************************************************************************
**      2019-05-20  HChromatismCollection 色容差数据集合。
***************************************************************************************************/

#ifndef HCHROMATISMCOLLECTION_H
#define HCHROMATISMCOLLECTION_H

#include "IChromatismCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HChromatismCollectionPrivate;

class HChromatismCollection : public IChromatismCollection
{
    Q_DECLARE_PRIVATE(HChromatismCollection)

public:
    explicit HChromatismCollection();
    virtual ~HChromatismCollection();

public:
    QString typeName() override;

public:
    double calcSdcm(double tc, QPointF xy) override;
    QJsonObject toJson() override;

protected:
    HChromatismCollection(HChromatismCollectionPrivate &);
};

HE_DATA_END_NAMESPACE

#endif // HCHROMATISMCOLLECTION_H
