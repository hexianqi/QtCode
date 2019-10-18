#ifndef HQUALITYITEMCOLLECTION_P_H
#define HQUALITYITEMCOLLECTION_P_H

#include "HQualityItemCollection.h"

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;

class HQualityItemCollectionPrivate : public HCollectionPrivate<IQualityItem>
{
public:
    HQualityItemCollectionPrivate();

public:
    IDataFactory *factory = nullptr;
};

HE_DATA_END_NAMESPACE

#endif // HQUALITYITEMCOLLECTION_P_H
