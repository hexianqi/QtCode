#pragma once

#include "HChromatismCollection.h"

HE_BEGIN_NAMESPACE

class HChromatismCollectionPrivate : public HDataCollectionPrivate<IChromatism>
{
public:
    HChromatismCollectionPrivate();

public:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);
};

HE_END_NAMESPACE
