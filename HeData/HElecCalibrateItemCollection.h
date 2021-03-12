/***************************************************************************************************
**      2019-10-17  HElecCalibrateItemCollection
***************************************************************************************************/

#pragma once

#include "IElecCalibrateItemCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HElecCalibrateItemCollectionPrivate;

class HElecCalibrateItemCollection : public IElecCalibrateItemCollection
{
    Q_DECLARE_PRIVATE(HElecCalibrateItemCollection)

public:
    explicit HElecCalibrateItemCollection();
    virtual ~HElecCalibrateItemCollection() = default;

public:
    void initialize(QVariantMap param) override;
    QString typeName() override;

public:
    void readContent(QDataStream &) override;
    void writeContent(QDataStream &) override;

protected:
    HElecCalibrateItemCollection(HElecCalibrateItemCollectionPrivate &);
};

HE_DATA_END_NAMESPACE
