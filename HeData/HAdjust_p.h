#ifndef HADJUST_P_H
#define HADJUST_P_H

#include "HAdjust.h"

HE_DATA_BEGIN_NAMESPACE

class IDataFactory;

class HAdjustPrivate : public HCollectionPrivate<IAdjustItem>
{
public:
    HAdjustPrivate();

public:
    IDataFactory *factory = nullptr;
};

HE_DATA_END_NAMESPACE

#endif // HADJUST_P_H
