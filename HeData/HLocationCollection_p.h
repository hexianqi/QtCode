#pragma once

#include "HLocationCollection.h"

HE_BEGIN_NAMESPACE

class HLocationCollectionPrivate : public HDataCollectionPrivate<ILocation>
{
public:
    HLocationCollectionPrivate();

public:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);
};

HE_END_NAMESPACE

