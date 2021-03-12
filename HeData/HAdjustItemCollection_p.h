#pragma once

#include "HAdjustItemCollection.h"

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;

class HAdjustItemCollectionPrivate : public HCollectionPrivate<IAdjustItem>
{
public:
    HAdjustItemCollectionPrivate();

public:
    IDataFactory *factory = nullptr;
    QVariantMap datas;
};

HE_DATA_END_NAMESPACE

