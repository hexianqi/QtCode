#pragma once

#include "HAdjust2Collection.h"

HE_BEGIN_NAMESPACE

class HAdjust2CollectionPrivate : public HDataCollectionPrivate<IAdjust2>
{
public:
    HAdjust2CollectionPrivate();

public:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);
};

HE_END_NAMESPACE

