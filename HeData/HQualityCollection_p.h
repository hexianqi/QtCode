#pragma once

#include "HQualityCollection.h"

HE_DATA_BEGIN_NAMESPACE

class HQualityCollectionPrivate : public HDataCollectionPrivate<IQuality>
{
public:
    HQualityCollectionPrivate();

public:
    void readContent(QDataStream &);
    void writeContent(QDataStream &);
};

HE_DATA_END_NAMESPACE
