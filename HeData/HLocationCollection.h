/***************************************************************************************************
**      2022-01-26  HLocationCollection
***************************************************************************************************/

#pragma once

#include "ILocationCollection.h"

HE_BEGIN_NAMESPACE

class HLocationCollectionPrivate;

class HLocationCollection : public ILocationCollection
{
    Q_DECLARE_PRIVATE(HLocationCollection)

public:
    explicit HLocationCollection();
    ~HLocationCollection();

public:
    QString typeName() override;

public:
    QRect boundingRect() override;
    QPolygon polygon() override;

protected:
    HLocationCollection(HLocationCollectionPrivate &);
};

HE_END_NAMESPACE

