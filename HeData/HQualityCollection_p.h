#pragma once

#include "HQualityCollection.h"

HE_BEGIN_NAMESPACE

class HQualityCollectionPrivate : public HDataCollectionPrivate<IQuality>
{
public:
    HQualityCollectionPrivate();

public:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);
};

HE_END_NAMESPACE
